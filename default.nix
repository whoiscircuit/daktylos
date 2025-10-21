{ pkgs ? import <nixpkgs> {},... }:
with pkgs; 
stdenv.mkDerivation rec {
    pname = "hidrosis";
    version = "0.1.0";
    src = ./hidrosis;
    cmakeFlags = [
        "-DCMAKE_POLICY_VERSION_MINIMUM=3.5"
    ];
    nativeBuildInputs = [cmake pkgconf clang patchelf];

    buildInputs = [
        libudev-zero libxkbcommon xorg.libX11 xorg.libxkbfile wayland libffi cjson
    ];

    installPhase = ''
      mkdir -p $out/bin
      cp app/hidrosis $out/bin/
      patchelf --replace-needed libcjson.so.1 ${cjson}/lib/libcjson.so.1 "$out/bin/hidrosis"
      patchelf --print-rpath "$out/bin/hidrosis"
      mkdir -p $out/etc/systemd/user
      cp ../packaging/linux/systemd/hidrosis.service $out/etc/systemd/user/
      mkdir -p $out/usr/lib/udev/rules.d/
      cp ../packaging/linux/90-hidrosis.rules $out/usr/lib/udev/rules.d/
    '';
}