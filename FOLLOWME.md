# C++ OpenGL Procedural Terrain Generation: Complete Setup Guide

## 1. Library Selection & Justification

### Core Libraries

**GLFW3** (Window & Input)
- Industry standard for OpenGL context creation
- Clean, minimal API with no hidden overhead
- Linux/Windows/macOS support
- Alternative: SDL2 (more general purpose, slightly heavier)
- *Why not others*: X11 direct is too low-level; Qt adds unnecessary coupling

**glad** (OpenGL Loader)
- Modern replacement for GLEW
- Generates exactly what you need (no bloat)
- Supports core profile specification
- Generated from web service; easier to maintain versions
- *Why not GLEW*: GLEW uses deprecated functions by default; glad is more explicit

**glm** (Math Library)
- GLSL-aligned types (vec3, mat4, etc.)
- No external dependencies
- Header-only (easy integration)
- Industry standard for graphics
- *Why not Eigen*: Overkill for graphics; glm is purpose-built

**FastNoise2** (Noise Generation)
- Modern C++ noise library
- Supports Perlin, Simplex, OpenSimplex2, Worley
- SIMD optimization built-in
- Easy FBM (fractal Brownian motion) composition
- *Why not libnoise*: Unmaintained; FastNoise2 is actively developed
- *Why not hand-rolled*: Premature optimization; use tested impl first

**stb_image** (Image Loading)
- Single header file, public domain
- Minimal dependency footprint
- Works with heightmaps from files
- *Why not SOIL/DevIL*: Overkill for this project; stb is sufficient

### Optional but Recommended

**Dear ImGui** (Debug GUI)
- Real-time parameter adjustment (scale, octaves, etc.)
- Minimal overhead
- Perfect for graphics debugging
- Single integration point (usually in main loop)

**spdlog** (Logging)
- Fast, header-only logging
- Better than printf for shader errors, init logs
- Optional but recommended for debugging

**Catch2** (Unit Testing)
- Noise function validation
- Mesh generation correctness
- Optional: only if you care about robustness

---

## 2. Project Architecture

### Folder Structure

```
terrain-project/
├── CMakeLists.txt
├── extern/
│   ├── CMakeLists.txt (manage all deps)
│   ├── glfw/
│   ├── glad/
│   ├── glm/
│   ├── FastNoise2/
│   └── stb/
├── src/
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── core/
│   │   ├── window.h / window.cpp
│   │   ├── renderer.h / renderer.cpp
│   │   └── shader.h / shader.cpp
│   ├── graphics/
│   │   ├── mesh.h / mesh.cpp
│   │   ├── camera.h / camera.cpp
│   │   └── light.h
│   ├── terrain/
│   │   ├── terrain.h / terrain.cpp
│   │   ├── noise_generator.h / noise_generator.cpp
│   │   └── heightmap.h / heightmap.cpp
│   └── utils/
│       ├── math_utils.h
│       └── file_io.h
├── shaders/
│   ├── terrain.vert
│   └── terrain.frag
└── assets/
    └── (heightmaps, config files)
```

### Class Responsibilities

**Window** (core/window.h)
- Wraps GLFW context creation
- Handles events (input, resize)
- Provides frame timing
- *Does NOT*: Know about graphics pipeline
- *Does NOT*: Handle rendering

**Shader** (core/shader.h)
- Compiles/links vertex + fragment shaders
- Uniform management (setVec3, setMat4, etc.)
- Error checking with proper logs
- *Does NOT*: Know about specific uniforms (camera position, light, etc.)—that's the caller's job

**Renderer** (core/renderer.h)
- High-level rendering orchestration
- Manages render state (clear color, depth test, culling)
- Calls draw on meshes and terrain
- Uses Camera and Light to set up uniforms
- *Does NOT*: Create meshes; that's owned elsewhere

**Camera** (graphics/camera.h)
- View/projection matrices
- Movement (WASD input driven from main)
- Frustum (optional: for LOD culling later)

**Mesh** (graphics/mesh.h)
- VAO/VBO/EBO management
- Draw calls (bind VAO, glDrawElements)
- Vertex format (pos, normal, color/texcoord)
- Immutable after construction (CPU-to-GPU one-time transfer)

**Heightmap** (terrain/heightmap.h)
- 2D float array storing heights
- Methods: sample(x, z), getHeight(x, z) with interpolation
- Optional: load from file (RAW, PNG via stb)

**NoiseGenerator** (terrain/noise_generator.h)
- Wraps FastNoise2
- Owns noise function parameters (scale, octaves, persistence, lacunarity)
- Method: generate(width, height, xOffset, zOffset) → std::vector<float>
- Exposes parameter tweaking (for ImGui integration)

**Terrain** (terrain/terrain.h)
- Owns Heightmap + Mesh
- Generates mesh from heightmap
- Computes normals
- Method: regenerate(NoiseGenerator) for parameter changes
- Optional: LOD chunks (advanced)

**Light** (graphics/light.h)
- Simple struct or lightweight class
- Direction, color, intensity
- Used by Renderer to set shader uniforms

---

## 3. CMake Build System

### Root CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.20)
project(TerrainGen CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find or add external dependencies
add_subdirectory(extern)

# Main library
add_subdirectory(src)

# Shader copying (automated)
add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/copy_shaders.cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# Optional: for MSVC, set startup project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT terrain_app)
```

### extern/CMakeLists.txt

```cmake
# GLFW
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory(glfw)

# glad (generated locally or via git submodule)
# Usually, you run glad generator online and drop files in extern/glad/
add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

# glm (header-only)
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE glm)

# FastNoise2
add_subdirectory(FastNoise2)

# stb (header-only)
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE stb)

# OpenGL (system)
find_package(OpenGL REQUIRED)

# Optional: Dear ImGui
add_library(imgui STATIC
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC imgui imgui/backends)
target_link_libraries(imgui PUBLIC glfw)
```

### src/CMakeLists.txt

```cmake
set(SOURCES
    main.cpp
    core/window.cpp
    core/shader.cpp
    core/renderer.cpp
    graphics/mesh.cpp
    graphics/camera.cpp
    terrain/terrain.cpp
    terrain/noise_generator.cpp
    terrain/heightmap.cpp
)

add_executable(terrain_app ${SOURCES})

target_include_directories(terrain_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(terrain_app PRIVATE
    glfw
    glad
    glm
    FastNoise2
    stb
    OpenGL::GL
    imgui
)

# On Linux: may need to link X11, pthreads for GLFW
if(UNIX AND NOT APPLE)
    target_link_libraries(terrain_app PRIVATE X11 pthread)
endif()
```

---

## 4. Rendering Pipeline

### Vertex Format & Data Layout

```cpp
struct Vertex {
    glm::vec3 position;      // 12 bytes
    glm::vec3 normal;        // 12 bytes
    glm::vec3 color;         // 12 bytes (or texcoord)
    // Total: 36 bytes per vertex
};
```

**VAO/VBO/EBO Strategy**

- **VAO**: Stores vertex attribute pointers (state)
- **VBO**: Single buffer for all vertices
- **EBO**: Index buffer (quad/triangle indices)

```cpp
class Mesh {
    GLuint VAO, VBO, EBO;
    size_t indexCount;
    
public:
    void create(const std::vector<Vertex>& vertices, 
                const std::vector<uint32_t>& indices) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        
        glBindVertexArray(VAO);
        
        // VBO: vertex data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, 
                     vertices.size() * sizeof(Vertex), 
                     vertices.data(), 
                     GL_STATIC_DRAW);
        
        // EBO: indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                     indices.size() * sizeof(uint32_t), 
                     indices.data(), 
                     GL_STATIC_DRAW);
        
        // Vertex attributes
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
                             sizeof(Vertex), 
                             (void*)offsetof(Vertex, position));
        
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 
                             sizeof(Vertex), 
                             (void*)offsetof(Vertex, normal));
        
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 
                             sizeof(Vertex), 
                             (void*)offsetof(Vertex, color));
        
        glBindVertexArray(0);
        indexCount = indices.size();
    }
    
    void draw() const {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
};
```

### Normal Calculation Strategy

**Per-Vertex Normals (Smooth)**

For grid-based terrain, compute face normals for each triangle, then average at vertices:

```cpp
void Terrain::computeNormals(std::vector<Vertex>& vertices, 
                              const std::vector<uint32_t>& indices) {
    // Initialize all normals to zero
    for (auto& v : vertices) v.normal = glm::vec3(0.0f);
    
    // Accumulate face normals
    for (size_t i = 0; i < indices.size(); i += 3) {
        uint32_t i0 = indices[i];
        uint32_t i1 = indices[i + 1];
        uint32_t i2 = indices[i + 2];
        
        glm::vec3 edge1 = vertices[i1].position - vertices[i0].position;
        glm::vec3 edge2 = vertices[i2].position - vertices[i0].position;
        glm::vec3 faceNormal = glm::cross(edge1, edge2);
        
        // Accumulate (unweighted for simplicity; could weight by angle)
        vertices[i0].normal += faceNormal;
        vertices[i1].normal += faceNormal;
        vertices[i2].normal += faceNormal;
    }
    
    // Normalize
    for (auto& v : vertices) {
        float len = glm::length(v.normal);
        if (len > 0.0001f) {
            v.normal = glm::normalize(v.normal);
        } else {
            v.normal = glm::vec3(0, 1, 0); // Fallback
        }
    }
}
```

**Why this approach:**
- Smooth lighting across terrain
- Avoids faceted appearance
- O(n) complexity
- Unweighted accumulation is acceptable for educational purposes (angle-weighting is more accurate but rarely visible)

### Lighting Model (Directional)

**Fragment Shader:**

```glsl
// terrain.frag
#version 330 core

in vec3 vNormal;
in vec3 vColor;
in vec3 vFragPos;

out vec4 FragColor;

uniform vec3 uLightDir;      // Normalized, pointing towards light
uniform vec3 uLightColor;
uniform float uLightIntensity;
uniform vec3 uViewPos;

void main() {
    vec3 norm = normalize(vNormal);
    
    // Diffuse
    float diff = max(dot(norm, uLightDir), 0.0);
    vec3 diffuse = diff * uLightColor * uLightIntensity;
    
    // Specular (Blinn-Phong)
    vec3 viewDir = normalize(uViewPos - vFragPos);
    vec3 halfDir = normalize(uLightDir + viewDir);
    float spec = pow(max(dot(norm, halfDir), 0.0), 32.0);
    vec3 specular = spec * uLightColor * 0.5;
    
    // Ambient
    vec3 ambient = vec3(0.1) * vColor;
    
    vec3 result = (ambient + diffuse * vColor + specular);
    FragColor = vec4(result, 1.0);
}
```

---

## 5. Terrain Generation

### Grid-Based Mesh Generation

```cpp
class Terrain {
    Heightmap heightmap;
    Mesh mesh;
    
public:
    void generate(const NoiseGenerator& noiseGen, 
                  uint32_t gridWidth, uint32_t gridHeight) {
        
        // Step 1: Generate heightmap
        heightmap.generate(noiseGen, gridWidth, gridHeight);
        
        // Step 2: Create vertex grid
        std::vector<Vertex> vertices;
        vertices.reserve(gridWidth * gridHeight);
        
        for (uint32_t z = 0; z < gridHeight; ++z) {
            for (uint32_t x = 0; x < gridWidth; ++x) {
                float height = heightmap.get(x, z);
                
                Vertex v;
                v.position = glm::vec3(x, height, z);
                v.color = colorFromHeight(height);
                v.normal = glm::vec3(0); // Will be computed
                
                vertices.push_back(v);
            }
        }
        
        // Step 3: Create indices (two triangles per quad)
        std::vector<uint32_t> indices;
        indices.reserve((gridWidth - 1) * (gridHeight - 1) * 6);
        
        for (uint32_t z = 0; z < gridHeight - 1; ++z) {
            for (uint32_t x = 0; x < gridWidth - 1; ++x) {
                uint32_t base = z * gridWidth + x;
                
                // First triangle (CCW)
                indices.push_back(base);
                indices.push_back(base + 1);
                indices.push_back(base + gridWidth);
                
                // Second triangle (CCW)
                indices.push_back(base + 1);
                indices.push_back(base + gridWidth + 1);
                indices.push_back(base + gridWidth);
            }
        }
        
        // Step 4: Compute normals
        computeNormals(vertices, indices);
        
        // Step 5: Upload to GPU
        mesh.create(vertices, indices);
    }
    
private:
    glm::vec3 colorFromHeight(float h) {
        // Simple height-based coloring
        if (h < 0.3f) return glm::vec3(0.2f, 0.4f, 0.8f);      // Water
        if (h < 0.5f) return glm::vec3(0.9f, 0.8f, 0.1f);      // Sand
        if (h < 0.7f) return glm::vec3(0.0f, 0.7f, 0.0f);      // Grass
        return glm::vec3(0.6f, 0.6f, 0.6f);                     // Rock
    }
};
```

### Noise Generation & Parameters

```cpp
class NoiseGenerator {
    FastNoise::SmartNode<FastNoise::Perlin> perlin;
    float scale = 50.0f;
    float amplitude = 1.0f;
    int octaves = 4;
    float lacunarity = 2.0f;
    float persistence = 0.5f;
    
public:
    NoiseGenerator() {
        perlin = FastNoise::New<FastNoise::Perlin>();
    }
    
    std::vector<float> generate(uint32_t width, uint32_t height,
                                float xOffset = 0.0f, 
                                float zOffset = 0.0f) {
        std::vector<float> heights(width * height);
        
        for (uint32_t z = 0; z < height; ++z) {
            for (uint32_t x = 0; x < width; ++x) {
                float value = fbm(x + xOffset, z + zOffset);
                heights[z * width + x] = value;
            }
        }
        
        return heights;
    }
    
private:
    float fbm(float x, float z) {
        float value = 0.0f;
        float maxValue = 0.0f;
        float freq = 1.0f;
        float amp = 1.0f;
        
        for (int i = 0; i < octaves; ++i) {
            float sampleX = x / scale * freq;
            float sampleZ = z / scale * freq;
            
            value += perlin->GenSingle2D(sampleX, sampleZ) * amp;
            maxValue += amp;
            
            freq *= lacunarity;
            amp *= persistence;
        }
        
        return value / maxValue; // Normalize to [0, 1]
    }
    
public:
    // Setters for ImGui
    void setScale(float s) { scale = s; }
    void setAmplitude(float a) { amplitude = a; }
    void setOctaves(int o) { octaves = glm::clamp(o, 1, 8); }
    void setLacunarity(float l) { lacunarity = l; }
    void setPersistence(float p) { persistence = glm::clamp(p, 0.0f, 1.0f); }
};
```

---

## 6. Shader Setup

### Vertex Shader (terrain.vert)

```glsl
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 vNormal;
out vec3 vColor;
out vec3 vFragPos;

void main() {
    vFragPos = vec3(uModel * vec4(aPosition, 1.0));
    vNormal = mat3(transpose(inverse(uModel))) * aNormal;
    vColor = aColor;
    
    gl_Position = uProjection * uView * vec4(vFragPos, 1.0);
}
```

**Responsibilities:**
- Transform position to world space (vFragPos)
- Transform normals to world space (accounting for non-uniform scaling)
- Pass interpolated data to fragment shader
- Does NOT apply lighting (that's per-fragment, more accurate)

### Fragment Shader (terrain.frag)

See Section 4.3 above—implements Phong/Blinn-Phong with height-based color.

**Why fragment-based lighting:**
- Per-pixel normals (interpolated from vertices)
- Smoother specular highlights
- Better performance than per-vertex with modern hardware

---

## 7. Common Pitfalls & Solutions

### Performance Issues

**Problem: Generating large terrains (>1024×1024) is slow**

**Solution:**
- Profile first: use `std::chrono` to time mesh generation vs. noise generation
- Noise generation typically dominates; parallelize with OpenMP
  ```cpp
  #pragma omp parallel for collapse(2)
  for (uint32_t z = 0; z < height; ++z) {
      for (uint32_t x = 0; x < width; ++x) {
          heights[z * width + x] = fbm(x, z);
      }
  }
  ```
- Normal computation: also parallelize (but sync before GPU upload)
- Future: Move FBM to GPU compute shader (much faster for real-time updates)

**Problem: Rendering stutters with multiple terrain chunks**

**Solution:**
- Use frustum culling (cull chunks outside view)
- Implement LOD: distant chunks use fewer vertices
- Consider vertex streaming (advanced): generate mesh on worker thread, double-buffer VBOs

### Normal Errors

**Problem: Terrain looks faceted despite per-vertex normals**

**Causes & fixes:**
1. **Incorrect normal accumulation**: Ensure cross product order is consistent (CCW)
   ```cpp
   // Correct (assuming CCW winding)
   glm::vec3 normal = glm::cross(edge1, edge2);
   ```
2. **Normals not normalized before per-fragment interpolation**: Renormalize in fragment shader
   ```glsl
   vec3 norm = normalize(vNormal);  // MUST do this
   ```
3. **Vertex normal pointing wrong direction**: Visual check—light from above, should see bright top
4. **Using mat3(uModel) instead of transpose(inverse(uModel))** for non-uniform scaling (if you have it)

**Problem: Lighting is too bright or too dim**

**Solution:** Debug by outputting normals as colors
```glsl
FragColor = vec4(normalize(vNormal) * 0.5 + 0.5, 1.0);  // Visualize normals
```
Cyan (0,1,1) = normals pointing up. If inconsistent, fix accumulation.

### Precision Issues with Large Terrains

**Problem: Vertices far from origin lose precision (floating point jitter)**

**Causes:**
- Float32 has ~6-7 decimal digits of precision
- A terrain at position (100,000, 0, 200,000) loses sub-unit precision

**Solutions:**
1. **Camera-relative positions**: Store terrain in world space, but subtract camera position in vertex shader
   ```glsl
   gl_Position = uProjection * uView * vec4(vFragPos - uCameraPos, 1.0);
   ```
2. **Chunk-based terrain**: Divide terrain into chunks, regenerate far chunks lazily
3. **Double precision (overkill)**: Use float64 for heightmap generation, downcast to float32 for GPU

**Problem: Heightmap values become denormalized with very steep heights**

**Solution:**
- Keep height range reasonable: [0, 255] or [-1, 1] normalized
- In mesh generation, scale: `height * verticalScale`
  ```cpp
  float height = heightmap.get(x, z) * 100.0f;  // Scale to ±100 units
  ```
- In noise FBM, clamp amplitude: `maxValue` sum prevents unbounded growth

**Problem: Normal calculation produces NaNs or zero vectors**

**Solution:**
- Always check length before normalizing
  ```cpp
  float len = glm::length(v.normal);
  if (len > 0.0001f) {
      v.normal = glm::normalize(v.normal);
  } else {
      v.normal = glm::vec3(0, 1, 0);  // Fallback
  }
  ```
- This handles flat areas (all vertices at same height) gracefully

### Debugging Checklist

- **Terrain appears black**: Check light direction (should point towards surface)
- **Terrain inverted**: Winding order (CCW vs CW) mismatch or normal flip
- **Terrain is flat**: Heightmap generation failed; add logging to NoiseGenerator
- **Shaders don't compile**: Save error log to file and read it—don't rely on console
- **Memory leaks**: Use Valgrind (Linux) or Visual Studio debugger; profile after 100 regenerations

---

## 8. Integration Flow (Pseudocode)

```cpp
int main() {
    Window window(1280, 720, "Terrain Generator");
    Renderer renderer;
    
    Camera camera(glm::vec3(512, 200, 512), glm::radians(45.0f));
    Light light(glm::normalize(glm::vec3(1, 1, 1)), 
                glm::vec3(1, 1, 1), 1.2f);
    
    NoiseGenerator noiseGen;
    Terrain terrain;
    terrain.generate(noiseGen, 512, 512);
    
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.getHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    while (!window.shouldClose()) {
        // Input
        window.pollEvents();
        camera.processInput(window);
        
        // ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("Terrain Settings");
            static float scale = 50.0f, persistence = 0.5f;
            static int octaves = 4;
            if (ImGui::SliderFloat("Scale", &scale, 10, 200)) {
                noiseGen.setScale(scale);
                terrain.generate(noiseGen, 512, 512);
            }
            if (ImGui::SliderInt("Octaves", &octaves, 1, 8)) {
                noiseGen.setOctaves(octaves);
                terrain.generate(noiseGen, 512, 512);
            }
            ImGui::SliderFloat("Persistence", &persistence, 0, 1);
            noiseGen.setPersistence(persistence);
            ImGui::End();
        }
        ImGui::Render();
        
        // Render
        renderer.clear();
        renderer.render(terrain, camera, light);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        window.swapBuffers();
    }
    
    ImGui::DestroyContext();
    return 0;
}
```

---

## 9. Next Steps (Extensibility)

Once the basic pipeline works:

1. **GPU Heightmap Generation**: Move noise FBM to compute shader
2. **LOD System**: Multiple mesh versions (detail vs. coarse), swap based on distance
3. **Mesh Streaming**: Background thread generates chunks, GPU uploads them
4. **Texturing**: Replace per-vertex color with texture coordinates + sampler
5. **Shadows**: Implement shadow mapping (directional light)
6. **Water Simulation**: GPU vertex displacement for waves
7. **Vegetation**: Instanced rendering of trees/grass based on heightmap

Each is a natural extension of this foundation.