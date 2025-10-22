{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs";
  };

  outputs = { self, nixpkgs }: 
  let 
    system = "x86_64-linux";
    pkgs = import nixpkgs {
      inherit system;
    };
    hidrosis = import ./default.nix {pkgs};
  in rec {
    packages.${system}.default = hidrosis;
    devShell = pkgs.mkShell {inputsFrom = hidrosis;};
    overlays.default = final: prev: {
      inherit hidrosis;
    };
    nixosModules.default = import ./module.nix;
  };
}
