function [ success ] = ardrone_unixinstaller()
%UNIXINSTALLER installs cross compilation toolchain on an unix system
%   This toolchain works for OSX and Linux distros
%   This 
%   For the windows installer, see wininstaller

%% Install cross compiler if it is not already installed
[status,cmdout] = unix('find /arm-none-linux-gnueabi') 

% check if gcc-arm-linux-gnueabi is installed
if strfind(cmdout,'No such file or directory'),
    disp('Cross compiler not found. Installing...');
    
    % install 32-bit libraries
    status = unix('sudo apt-get install libc6:i386 libstdc++6:i386')
    if (status ~= 0),
        disp('32-bit libraries did not install properly. Exiting...');
        success = -1;
        return;
    end;
    
    % fetch cross compiler from web
    status = unix('wget -c -O ~/Downloads/arm-2013.05-24-arm-none-linux-gnueabi-i686-pc-linux-gnu.tar.bz2 http://sourcery.mentor.com/public/gnu_toolchain/arm-none-linux-gnueabi/arm-2013.05-24-arm-none-linux-gnueabi-i686-pc-linux-gnu.tar.bz2')
    if (status ~= 0),
        disp('wget did not execute properly. Exiting...');
        success = -1;
        return;
    end;
    
    % unpack toolchain tarball
    status = unix('cd ~/Downloads')
    if (status ~= 0),
        disp('cd did not execute properly. Exiting...');
        success = -1;
        return;
    end;
    
    status = unix('tar -xvf ~/Downloads/arm-2013.05-24-arm-none-linux-gnueabi-i686-pc-linux-gnu.tar.bz2')
    if (status ~= 0),
        disp('tar did not execute properly. Exiting...');
        success = -1;
        return;
    end;
    
    % Make a directory at the home directory to hold compiler
    status = unix('sudo mkdir /arm-none-linux-gnueabi')
    if (status ~= 0),
        disp('mkdir did not execute properly. Exiting...');
        success = -1;
        return;
    end;
    
    % Move compiler to home directory
    status = unix('sudo mv -f arm-2013.05/* /arm-none-linux-gnueabi')
    if (status ~= 0),
        disp('mv did not execute properly. Exiting...');
        success = -1;
        return;
    end;
    
    % create soft link
    unix('ln -s /arm-none-linux-gnueabi/bin/ /usr/local/bin/')
    
    % clean up
    unix('cd ~/Downloads')
    unix('sudo rm ~/Downloads/arm-2013.05-24-arm-none-linux-gnueabi-i686-pc-linux-gnu.tar.bz2')
    
end;

success = status;

end

