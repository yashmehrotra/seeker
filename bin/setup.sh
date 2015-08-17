# For setting up Go
# Let's Go

sudo apt-get install -y golang

# Set path variable
# in your .bashrc, .zshrc , .profice etc
export PATH=$PATH:/usr/local/go/bin

# For package management
mkdir $HOME/go
export GOPATH=$HOME/go
export PATH=$PATH:$GOPATH/bin
