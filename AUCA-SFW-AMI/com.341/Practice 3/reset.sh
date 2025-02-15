#!/bin/bash
fusermount -u mount/ 
rm -r mount/ 
./create_file_system.krffs.sh
mkdir mount
./krffs file_system.krffs mount/