# WebSocketWithOpenCV Project

This project is a WebSocket server that uses Boost, OpenCV, and C++ to perform
image processing. The server processes images, detects edges, and sends a
confirmation message to the client upon completion. The project includes
support for displaying processed images on the backend and can be configured to
save output images instead.

## Installation

### With Nix

The preferred way to build this project is with the Nix package manager, which
builds in a hermetically sealed and reproducible build environment as well as
providing critical build dependencies. Nix will automatically manage the build
and orchestrate CMake and `make`.

Note that Nix is only supported on macOS and Linux. Windows users should use
first install the [Windows Subsystem for Linux
(WSL)](https://learn.microsoft.com/en-us/windows/wsl/install) and then follow
the below instructions.

1. Install Nix:

```bash
curl --proto '=https' --tlsv1.2 -sSf -L \
  https://install.determinate.systems/nix | sh -s -- install --determinate
```

> [!IMPORTANT]
> If you already have Nix installed and did not use the above installer, you
> must enable the experimental "flakes" and "nix-command" features.

2. Build the program
``` bash
nix build
```

3. Run the program
```bash
result/bin/WebSocketWithOpenCV
```

Alternatively, build and run it in one step with

```bash
nix run
```

## Hacking

To hack on the code, it is not convenient to re-run `nix build` upon every code
change. A [devenv](https://devenv.sh/) development shell is provided so you
can directly execute `cmake .` and take advantage of CMake's caching features
and tooling.

Follow the instructions to install `nix` as detailed above, then run

```bash
nix develop
```

You will enter a `bash` shell where you can execute `cmake`. All build
dependencies (such as boost, openCV, etc) are provided in this shell.

You can run `cmake .` followed by `make` to compile the project.

Alternatively, if you want to retain your current shell environment, you can
install [direnv](https://direnv.net/), then run

```bash
direnv allow
```

Now, your shell will automatically be hooked into the development environment
as soon as you enter the project root.

The development shell also provides the `clang` and `clangd` LSP binaries for
convenience.


## Quick-and-dirty solution (Will Work without any downloads to package managers)

Before setting up this project, ensure that the following libraries and tools
are installed on your system:

> [!NOTE]
> These are only required when compiling manually. When building with Nix, all
> dependencies are provided automatically.


- **Boost** (including Boost.Asio and Boost.Beast)
- **OpenCV** (version 4.0 or higher)
- **libtorch** (v2.5.0 or higher)

./install_dependencies.sh is a quick solution to install all of them in your libs folder in this project repo!

- **A C++ Compiler** (supporting C++17 or higher)
- **CMake** (version 3.10 or higher)

Using this approach, you will have to manually provide the dependencies above,
placing them somewhere that `CMake` can find them.

1. **Clone the Repository**
   ```bash
   git clone <repository-url>
   cd WebSocketWithOpenCV

2. **Install dependencies**
*If you already have dependencies on your computer*
I still recommend you to have a libs folder that includes the cloned version of all the required dependencies(Both headers and the compiled code). 
It is then set up in the CmakeList to then find it relative to your project directory. If you don't then it still works, I'll made it so cmake accounts 
for that! 

*If you want to install all separate from any other projects, just in this project folder*
Simply run install_dependencies.sh by doing:
```bash
  ./install_dependencies.sh
```

Debugging statements are there to help you. 

3. **Build and server**
Just do ./build.sh
