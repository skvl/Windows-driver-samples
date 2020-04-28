# How to install BuildTools and WDK

From [here](https://social.msdn.microsoft.com/Forums/en-US/efe5f9f8-c32d-4a25-87e2-abbe711dadbb/no-wdk-support-for-visual-studio-2017-build-tools?forum=wdk):
```
Not sure if this is the best place to ask for this feature. I previously tried at:
https://github.com/MicrosoftDocs/windows-driver-docs/issues/1042 but that might have been the wrong place.

After installing Visual Studio 2017 Build Tools for C++ and the latest WDK, I get the following error when attempting to build a driver:

> MSB8020: The build tools for WindowsKernelModeDriver10.0 (Platform Toolset = 'WindowsKernelModeDriver10.0') cannot be found. [...]

Which is unsurprising, considering that the documentation mentions:

> The following editions of Visual Studio 2017 support driver development:
> * Download Visual Studio Community 2017
> * Download Visual Studio Professional 2017
> * Download Visual Studio Enterprise 2017

But this seems an unnecessary restriction, I've managed to use the "*WDK for Windows 10, version 1809*" with just the Build Tools by installing the WDK as usual, and then doing the following:

1. Downloading https://download.microsoft.com/download/7/D/D/7DD48DE6-8BDA-47C0-854A-539A800FAA90/wdk/Installers/dea2aa4848bad1eb522decedb8742d0c.cab 
2. Extracting *fil44a1ccbc56b9821e5022d37895cd1448* and opening it as *ZIP*.
3. Extracting *$VCTargets*, renaming it to *VCTargets*, and merging it with:
`C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\Common7\IDE\VC\VCTargets`.

I understand this type of installation is really hacky, and I'd rather avoid it, so here's my question: Has official support for Visual Studio 2017 Build Tools been considered?

It's the preferred (and sometimes only) tool available in some CI systems (e.g. TravisCI), and EWDK and full Visual Studio installations are comparatively too oversized.

-----

Alex. Jakob from WDK team here. We are huge fans of the Buildt Tools SKU. And indeed copying a few folders manually is all that is required to make WDK work well with Build Tools. Your request is noted. Let us see if we can get this to work in an official and automated manner. Can’t give you a date at this moment. With respect to your “hack” solution you are actually doing very similar to what a final solution in reality will iimplemdo underneath the hood. I will make suggestion that you after Build Tools and WDK installation do hack as follows: 1) find WDK.vsix in WDK root folder 2) rename to WDK.zip. 3) unzip. 4) Place content as you outline above.
```

# Links:
* [MSBuild on the command line - C++](https://docs.microsoft.com/en-us/cpp/build/msbuild-visual-cpp?view=vs-2019)
* [Visual Studio 2017 Build Tools 15.9.22.0](https://download.visualstudio.microsoft.com/download/pr/dfb60031-5f2b-4236-a36b-25a0197459bc/2f9a69561f6678f745b55ea38a606180b3941637d7e8cbbb65acae6933152d3e/vs_BuildTools.exe)
* [WDK 1809 10.0.17763.1](https://docs.microsoft.com/en-us/windows-hardware/drivers/other-wdk-downloads#step-2-install-the-wdk)
* [INF Files. Using Dirids](https://docs.microsoft.com/en-us/windows-hardware/drivers/install/using-dirids)