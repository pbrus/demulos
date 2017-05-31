# Demulos [![GitHub release](http://www.astro.uni.wroc.pl/ludzie/brus/img/github/ver20170531.svg "download")](https://github.com/pbrus/demulos/) ![Written in C](http://www.astro.uni.wroc.pl/ludzie/brus/img/github/c.svg "language") ![Written in Bash](http://www.astro.uni.wroc.pl/ludzie/brus/img/github/bash.svg "language") ![Written in AWK](http://www.astro.uni.wroc.pl/ludzie/brus/img/github/awk.svg "language") ![Written in Python](http://www.astro.uni.wroc.pl/ludzie/brus/img/github/python.svg "language")

Program allows to select isolated stars in crowded fields. These stars can be used to determine the PSF model on an image.

![demulos](http://www.astro.uni.wroc.pl/ludzie/brus/img/github/demulos.gif)

## Installation

Download the package wherever you want. In the next step call the installation script using *bash*:
```bash
$ bash install
```
and set the destination directory for `demulos` and `fwhm_av.py` programs. Due to the fact that:

 * you may have a lot of directories containing data from different observatories
 * some parameters can be set inside the `demulos.bash` script

`demulos.bash` should be always located at the working directory (just make copies of the script to spread it into directories). Moreover you should have installed `peak` and `dfits` programs from [the ESO eclipse library](https://www.eso.org/sci/software/eclipse/). I recommend to download the latest version: ftp://ftp.eso.org/pub/eclipse/eclipse-5.0.0/eclipse-main-5.0.0.tar.gz and compilte it according to *INSTALL* file.

## Usage

To use the program you need to prepare a single image in *FITS* format and a list of all stars in a text file. Both must be located at the working directory. Let's assume that an image is called `image.fits` and a list of all stars is called `stars.dat`. Before starting open the `demulos.bash` file and set some variables in the *SET PARAMETERS* section at the beginning of the script. Now it's time to run the program. Type into the terminal window:
```bash
$ ./demulos.bash --list stars.dat --image image.fits
```
These two arguments are mandatory. There is also one additional parameter which can be either set from the command line or in the *SET PARAMETERS* section:
```bash
$ ./demulos.bash --image image.fits --diff-mag 2.5 --list stars.dat
```
Note that the order of the arguments doesn't matter. After all the program generates the output file called `stars.dat-demulos` which contains isolated stars. This list can be used to determine the PSF model, particularly in dense stellar fields.

I encourage to visit my website to see more detailed description of this program. The current link can be found on my [GitHub profile](https://github.com/pbrus).

## License

**Demulos** is licensed under the [MIT license](http://opensource.org/licenses/MIT).
