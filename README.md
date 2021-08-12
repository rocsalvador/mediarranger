# mediarranger
A simple bash script to arrange photos and videos by years and months
## Dependencies
- exif
- mediainfo
## Installation
Run the following commands:
```bash
git clone https://github.com/rocsalvador/mediarranger && cd mediarranger
```
```bash
sudo ./installer.sh
```
To uninstall it:
```bash
sudo ./installer.sh -r
```
## Usage
```bash
mediarranger -s /path/to/source/dir -o /path/to/output/dir [OPTIONS]
OPTIONS:
-r | --recursive      All subdirectories of the source directory will be checked
```
