# Touchstone Viewer

Touchstone Viewer is a professional application for visualizing S-parameter data from Touchstone files. It provides a clean, customizable interface for analyzing RF measurement data with real-time rendering of S11 parameters in LogMag (dB) format.

## Features

- **Touchstone File Support**: Load and parse .s1p, .s2p, .snp files
- **LogMag Visualization**: Display S11 parameters in dB scale
- **Custom Rendering Engine**: Pure Qt implementation without external chart libraries
- **Real-time Customization**:
  - Adjust grid and line colors
  - Configure axis ticks count
  - Reload view without re-opening file
- **Professional Scaling**: Automatic unit conversion (Hz, kHz, MHz, GHz)
- **Error Handling**: Detailed error messages with modal dialogs
- **Responsive UI**: Loading indicators and smooth interactions

## Requirements

- **Operating System**: Windows 11
- **Qt**: Version 6.6.3
- **Compiler**: MinGW 11.2.0 (64-bit)
- **Build System**: CMake 3.20+

## Build Instructions

### 1. Install Prerequisites

- [Qt 6.6.3](https://www.qt.io/download-qt-installer) (select MinGW 11.2.0 during installation)
- [CMake](https://cmake.org/download/)
- [Git](https://git-scm.com/downloads)

### 2. Configure Environment Variables

**Add to system PATH:**

- C:\Qt\6.6.3\mingw_64\bin (usualy)
- C:\Qt\Tools\mingw1120_64\bin (usualy)
- C:\Program Files\CMake\bin (usualy)



### 3. Build Application

```bash
# Clone repository
git clone https://github.com/Devilartimus/Touchstone.git
cd Touchstone

# Create build directory
mkdir build
cd build

# Compile
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="your_directory_to_cmake" ..

# Builds
cmake --build .
```

### 3. Start Application
```bash
./TouchstoneViewer
```


## User Guide
### Loading Files

- Click "Load Touchstone File" button
- Select a valid Touchstone file (.s1p, .s2p, .snp)
- View automatically rendered S11 LogMag plot


### Customizing Display

- Grid Color: Click color picker next to "Grid" label
- Line Color: Click color picker next to "Line" label
- X Ticks: Set number of horizontal divisions (3-20)
- Y Ticks: Set number of vertical divisions (3-20)
- Reload: Apply changes without reloading file
