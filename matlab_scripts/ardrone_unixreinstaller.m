function [ success ] = ardrone_unixreinstaller()
% UNIXINSTALLER replaces an installation of cross compilation toolchain on an unix system
%   This toolchain works for OSX and Linux distros
%   For the windows installer, see wininstaller

% move to root
status = unix('cd /')
if (status ~= 0),
    disp('cd did not execute properly. Exiting...');
    success = -1;
    return;
end;
    
% remove the toolchain
status = unix('sudo rm -rf /arm-none-linux-gnueabi')
if (status ~= 0),
    disp('rm did not execute properly. Exiting...');
    success = -1;
    return;
end;

% call installer
ardrone_unixinstaller()

end