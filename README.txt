Author: Tyler Kemme
Email: tpkemme@gmail.com

Files

You will need:
 The VMware Player: http://www.vmware.com/products/player/
 The virtual machine image: http://www.cs.utexas.edu/~shmat/courses/cs361s/
cs361s-proj2vm.tar.bz2
 The project les: http://www.cs.utexas.edu/~shmat/courses/cs361s/cs361s-proj2.
tar.bz2
VMware environment
You will test your exploit programs in a VMware virtual machine. To do this, you will need
to download the virtual machine image as well as the VMware Player from VMware's website
(see above). VMware Player can run on Linux, Windows, and Mac OS X (VMware Fusion).
The virtual machine we provide is congured with Debian Etch. Should you need any
other packages to do your work (e.g., emacs), you can install it with the command apt-get
(e.g., apt-get install emacs). You may need to edit the /etc/apt/sources.list le and
replace http://mirrors.kernel.org/debian with http://archive.debian.org/debian
everywhere.
The virtual machine is congured to use NAT for networking. From the virtual machine,
you can type ifconfig as root to see the IP address of the virtual machine. It should be
listed under the eld inet addr: under eth0.
The virtual machine also has an SSH server. You can SSH into the virtual machine from
your machine, using the IP address produced by ifconfig (see above) as the destination.
You can also use this to transfer les onto the virtual machine using scp. Alternatively, you
can fetch les directly from the web on the VM using wget.

these files successfully exploit targets 1-4