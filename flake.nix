{
  description = "PlatformIO DevShell";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { nixpkgs, utils, ... }:
  utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs { inherit system; };
    in {
      devShells.default = pkgs.mkShell {
        name = "chaos.badge-shell";
        buildInputs = with pkgs; [
          ccls
          just
          openocd
          platformio
        ];
      };
    }
  );
}
