
# An example COM server and client (Protoss COM library)

## What does this repository contain?

This repository contains an example COM+ server and client implementation. Please read the [blog post on my blog](https://lowleveldesign.org/2022/01/17/com-revisited) to learn more about it.

## How do I build it?

To build the repository, you need Visual Studio 2022 with Windows SDK. You also need [vcpkg](https://vcpkg.io/en/index.html), configured with Visual Studio and the wil package (`vcpkg install wil`).

## How do I run it?

Build the solution and install the protoss.dll COM server:

```
regsvr32.exe protoss.dll
```

Then you may build and run the native (ProtossComClient) or managed (ProtossComManagedClient) client.
