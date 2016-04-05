# Unit Testing

You need to install [googletest][1] in order to build and run the unit tests. For
detailed instructions, please see the their Github website. If you are running a
linux system, then you can probably install them via your package manager.

For Debian-like systems, you can run

```bash
apt-cache search gtest # to search for the package and correct name
sudo apt-get install libgtest-dev # to install the package
```

If your package manager does not find any packages, then you'll probably have to
install it from source, but it is more likely that your package manager will find
more than one package with the word *gtest* embedded in the name of the package.
If you are not certain which one it is, you can run

```bash
apt-cache show PACKAGE # where PACKAGE is the name of the package
```

[1]: https://github.com/google/googletest
