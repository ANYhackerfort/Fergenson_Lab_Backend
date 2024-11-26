{
  cmake,
  libtorch-bin,
  boost,
  opencv,
  liboai,
  meson,
  ninja,
  pkg-config,
  llvmPackages_19,
  lib,
}:
llvmPackages_19.stdenv.mkDerivation (finalAttrs: {
  pname = "WebSocketWithOpenCV";
  version = "0.1.0";

  src = ../.;

  nativeBuildInputs = [
    meson
    ninja
    cmake
    pkg-config
    liboai
  ];

  buildInputs = [
    boost
    opencv
    libtorch-bin
    liboai
  ];

  installPhase = ''
    mkdir -p $out/bin
    cp WebSocketWithOpenCV $out/bin
  '';

  mesonFlags = [
    "-Dliboai_include_path=${liboai}/include"
    "-Dliboai_lib_path=${liboai}/lib"
  ];

  meta = {
    maintainers = [ lib.maintainers.youwen5 ];
    mainProgram = "WebSocketWithOpenCV";
  };
})
