
## FlappyBird: A RayLib and C++ Exploration

This project is a reimplementation of the classic  **FlappyBird**  game, built from scratch using  **C++**  and the powerful, simple  **RayLib**  library for rendering. A key design goal was to avoid pre-built game engines and focus instead on understanding core game development principles, language features, and code optimization.

----------

### Getting Started

To build and run this project, you will need a **C++ compiler**,  **CMake**  for building, and the  **RayLib**  library.

#### Prerequisites

-   **C++ Compiler:**  A modern C++ compiler (e.g., GCC, Clang, MSVC) that supports C++11 or later.
    
-   **CMake:**  A cross-platform build system. You can download it from the  [official CMake website](https://cmake.org/download/).
    
-   **RayLib:**  This project depends on the  **RayLib**  game programming library.
    
    -   The project's  `CMakeList.txt`  is configured to fetch and use RayLib automatically as a sub-module, simplifying the dependency setup. No manual installation of RayLib is typically required on the user's end, provided you have a working internet connection during the build process.
        

#### How to Build and Run

Follow these steps from your terminal to clone, build, and execute the game:

1.  **Open the Root directory in terminal:**  Navigate to the root directory of the cloned project.
    
2.  **Create and enter the build directory:**
    
    ```
    mkdir build
    cd build
    
    ```
    
3.  **Configure the build using CMake:**  This step generates the necessary build files (including fetching RayLib).
    
    ```
    cmake ..
    
    ```
    
4.  **Build the executable:**
    
    ```
    cmake --build .
    
    ```
    
5.  **Run the game:**
  
    ```
    ./FlappyBird
    
    ```
    

----------

### Controls

The controls are simple, reflecting the original game:

-   **Jump:**  Press the  **Space**  bar or the  **Arrow UP**  key.
    

----------

### Functionality and Code Structure

I implemented the code with a focus on  **modularity**  and the  **separation of concerns**. The project follows a simple but effective architectural pattern, dividing responsibilities into distinct files:

-   **`Main.cpp`:**  This is the entry point of the application. Its primary role is to manage the  **game states**  (e.g., Menu Screen, Playing, Game Over) and handle the overall game loop, calling into the other modules as necessary for updates and rendering.
    
-   **`Solver.cpp`  /  `Solver.h`:**  This module is the "brain" of the game. It contains the core  **game logic and physics calculations**. This includes updating the bird's position based on gravity and jumps, bird's rotation, managing the pipeline's movement, recycling pipes, detecting collisions, etc. By isolating calculations here, the rest of the code remains clean and focused.
    
-   **`Renderer.cpp`  /  `Renderer.h`:**  This module handles everything related to the visual representation. It is responsible for  **importing and managing assets**  and executing all the  **RayLib rendering calls**  to draw the bird, pipes, score, and background onto the screen. 
    

----------

### Design Philosophy and Technical Learnings

Building FlappyBird in C++ without a game engine was an intentional choice to deepen my understanding of the language and game development fundamentals.

#### 1. Optimization and Low-Level Control

One of the most rewarding aspects was the focus on  **optimization**  and understanding how C++ executes code:

-   **Collision System Improvement:**  I managed to refine the collision detection system, moving its complexity from an inefficient  **O(N)**  (where N is the number of pipes, representing a list of collision checks) to a highly efficient  **O(1)**. This ensures that the game's performance remains consistent and fast, regardless of the number of elements checked in a given frame.
    
-   **Bitwise Operations for Performance:**  To maximize speed, I consciously avoided the standard division operator (`/`). Instead, I used the  **right-shift bitwise operator (`>>`)** for divisions by powers of two and  **multiplication (`*`)** for other divisions . This is because integer division is notoriously slow on most architectures, and these low-level replacements offer a significant speed boost where applicable.
    

#### 2. Functional Programming Principles

The code base incorporates  **Functional Programming (FP) principles**  where appropriate. This means that functions are primarily treated as self-contained units that take inputs and return outputs without modifying global state (i.e., they are  **pure functions**). This approach enhances the code's:

-   **Readability:**  It is easier to trace the logic flow.
    
-   **Testability:**  Individual components can be tested in isolation.
    
-   **Predictability:**  The same input will always produce the same output, making debugging simpler.
    

#### 3. Structured Code Development

This project served as an excellent exercise in  **structuring a C++ application**. By keeping the project small, I was able to concentrate on proper file organization, clear interface definitions (headers), and maintainable class/struct design, which are crucial skills for building larger, more complex applications in the future.
