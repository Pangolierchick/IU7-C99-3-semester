from distutils.core import setup, Extension

def main():
    setup(name="arraylib",
            version="0.1.0",
            description="My wrapper",
            author="Pango",
            author_email="<---->",
            ext_modules=[Extension("arraylib",["./libarr/pywrap.c"], include_dirs=["../inc/libarr"], libraries=["ar"])])

if __name__ == "__main__":
    main()
