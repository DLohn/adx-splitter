# adx-splitter
Splits a multichannel ADX audio file to separate files.
Useful when attempting to extract audio from .adx files when existing converters have failed, as some were made under the assumption there are only 1 or 2 channels present.
Splitting each channel to a separate file allows the conversion to more conventional formats to go unhindered.
## Usage (Windows)
```shell
./adxsplitter.exe  input.adx
```
Output is input_0.adx, input_1.adx, input_2.adx, etc. One file corresponds to one channel of the input.
