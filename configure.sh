set -eu

function download_from_github
{
	if [ ! -f ${2} ]; then
		echo "Downloading ${1}"
		curl "https://raw.githubusercontent.com/${1}" > ${2}
	fi
}

mkdir -p libs
mkdir -p output
download_from_github "nothings/stb/master/stb_image.h"       "libs/stb_image.h"
download_from_github "nothings/stb/master/stb_image_write.h" "libs/stb_image_write.h"

if [ ! -d "libs/emilib" ]; then
	git clone git@github.com:emilk/emilib.git libs/emilib
fi