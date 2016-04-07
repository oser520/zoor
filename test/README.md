# Unit Testing

You need to install [googletest][1] in order to build and run the unit tests. For
detailed instructions, please see the their Github website. If you are running a
linux system, then you can probably install them via your package manager.

### For Debian (or a derivation)

Use these commands to search for and install the package.

```bash
sudo apt-cache search gtest
sudo apt-get install REAL_PACKAGE_NAME
```

If you get a list of packages with *gtest* embedded in the name, then you can
use the command below to get more information about a given package.

```bash
apt-cache show PACKAGE
```

### For RHEL (or a derivation)

These commands do the same as the commands listed above.

```bash
sudo yum search gtest
sudo yum install REAL_PACKAGE_NAME
```

```bash
sudo yum info PACKAGE
```

[1]: https://github.com/google/googletest
