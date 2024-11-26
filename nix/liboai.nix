{
  curl,
  nlohmann_json,
  cmake,
  fetchFromGitHub,
  llvmPackages_19,
}:
llvmPackages_19.stdenv.mkDerivation (finalAttrs: {
  pname = "oai";
  version = "4.0.1";

  src = fetchFromGitHub {
    owner = "D7EAD";
    repo = "liboai";
    rev = "v${finalAttrs.version}";
    hash = "sha256-hC1JVHImRpTrAjLKbt2ar84o1T6cD8mZyqYiJuAnnFM=";
  };

  nativeBuildInputs = [
    cmake
    curl.dev
    nlohmann_json
  ];

  propagatedBuildInputs = [
    curl.dev
    nlohmann_json
  ];

  preConfigure = ''
    cd liboai
  '';

  postInstall = ''
    # copy header to correct location (CMakeLists.txt does not specify properly)
    cp ../include/liboai.h $out/include
  '';
})
