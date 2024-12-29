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
and orchestrate `meson` and `ninja`.

Note that Nix is only supported on macOS and Linux. Windows users should use
first install the [Windows Subsystem for Linux
(WSL)](https://learn.microsoft.com/en-us/windows/wsl/install) and then follow
the below instructions.

1. Install Nix:

```bash
curl --proto '=https' --tlsv1.2 -sSf -L https://install.determinate.systems/nix | \
  sh -s -- install
```

> [!IMPORTANT]
> If you already have Nix installed and did not use the above installer, you
> must enable the experimental "flakes" and "nix-command" features.

2. Build the program

```bash
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
change. A [devenv](https://devenv.sh/) development shell is provided so you can
directly execute `meson`, `ninja`, and take advantage of incremental
compilation.

> [!IMPORTANT]
> It is highly recommended that you use the methods described below if you are
> going to be hacking (developing) on the code. Directly invoking `ninja`
> vastly speeds up subsequent compile times, since Nix cannot take advantage of
> incremental compilation.

Follow the instructions to install `nix` as detailed above, then run

```bash
nix develop --impure
```

Alternatively, if you want to retain your current shell environment and
seamlessly layer the development environment over it, you can install
[direnv](https://direnv.net/), then run

```bash
direnv allow
```

Now, your shell will automatically be hooked into the development environment
as soon as you enter the project root.

The development shell provides various pieces of tooling like `meson`, `ninja`,
`pkg-config`, etc. It also provides the libraries and dependencies necessary to
build the project.

Once you are in the development environment, run

```bash
meson setup build
```

This will use `meson` to generate the `build/` directory containing build
orchestration files. If you are using a language service like `clangd`, this
also provides the `compile_commmands.json` required for it to work properly.

Enter the directory and execute `ninja`:

```bash
cd build
ninja
```

This will produce the `WebSocketWithOpenCV` binary.

> [!IMPORTANT]
> If you add new libraries to Nix and `meson.build`, it is likely you will have
> to `rm -rf` the build directory and regenerate it with the commands above,
> due to some quirks with the Nix environment.
>
> Additionally, you should `exit` the `nix develop` shell and re-run `nix
develop --impure` if you modify any `nix` files.

## Formatter

The `treefmt` autoformatter has been configured in
[treefmt.toml](./treefmt.toml) to automatically format the entire tree.

To invoke it, please install Nix, then run:

```sh
nix fmt
```

We recommend you run this commmand before any commit to ensure your code meets
quality guidelines. Continuous integration will run on all commits to ensure
lints and formatting checks pass.

## Solution without package managers, only Meson

> [!WARNING]
> This approach is not recommended and should only be used if Nix is strictly not
> available for whatever reason.

Before setting up this project, ensure that the following libraries and tools
are installed on your system:

> [!NOTE]
> These are only required when compiling manually. When building with Nix, all
> dependencies are provided automatically.

- **Boost** (including Boost.Asio and Boost.Beast)
- **OpenCV** (version 4.0 or higher)
- **libtorch** (v2.5.0 or higher)
- **liboai** (v0.4.1 or higher)
- **A C++ Compiler** (supporting C++17 or higher, preferably clang)
- **CMake** (version 3.10 or higher, required to find dependencies)
- **Ninja**
- **Meson**
- **nlohmann-json** (version 3.11.3 or higher)
- **libcurl 7.78.0** (version 3.10 or higher)

Using this approach, you will have to manually provide the dependencies above,
placing them somewhere that `pkg-config` or `CMake` or `Meson` can find them.

1. **Clone the Repository**

   ```bash
   git clone <repository-url>
   cd WebSocketWithOpenCV

   ```

2. **Install dependencies** _If you already have dependencies on your computer_
   I still recommend you to have a libs folder that includes the cloned version
   of all the required dependencies(Both headers and the compiled code). It is
   then set up in the CmakeList to then find it relative to your project
   directory. If you don't then it still works, I'll made it so cmake accounts
   for that!

3. **Build and server**
   (1) `meson setup build && cd build`
   (2) `ninja`
