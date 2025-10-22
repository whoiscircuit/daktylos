{config,lib, pkgs,...}: 
let
  cfg = config.services.hidrosis;
  hidrosis = pkgs.callPackage ./default.nix {inherit pkgs; };
in
{
    options.services.hidrosis = {
        enable = lib.mkEnableOption "Enable hidrosis service and udev rule";
    };

    config = lib.mkIf cfg.enable {
        services.udev.packages = [ hidrosis ];

        systemd.user.services.hidrosis = {
            unitConfig = {
                SourcePath = "${hidrosis}/lib/systemd/user/hidrosis.service";
            };
        };
        
        environment.systemPackages = [ hidrosis ];
    };
}