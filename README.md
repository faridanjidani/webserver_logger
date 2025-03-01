<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#building-the-project">Building the Project</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
  </ol>
</details>




<!-- ABOUT THE PROJECT -->
## About The Project
This is a simple object oriented webserver logger that has been designed in C++. There are 4 different stages:
* `LogReceiver` reads a log file and sends each entry to logParser.
* `LogParser` extracts details from each log line.
* `StatsCollector` processes the parsed entry, updating metrics.
* `Metrics` (SuccessfulURICounter, HostAccessCounter) track specific stats.
* `ResultFormatter` organizes and formats the results for output.


<!-- GETTING STARTED -->
## Getting Started

### Prerequisites
- **CMake** (version 3.10 or higher)
- A C++ compiler (e.g., GCC, Clang, or MSVC)

### Building the Project
1. Clone the repository:
   ```bash
   git clone https://github.com/faridanjidani/webserver_logger.git
   cd webserver_logger
2. Initialize and Update Submodules:
    ```bash
    git submodule update --init --recursive
3. Create a build directory and navigate into it:
    ```bash
    mkdir build
    cd build
4. Generate the build files using CMake and build the project:
    ```bash
    cmake ..
    make 
5. To run the executable file use the command below with the address to the raw input file. 
    ```bash
    ./WebServerLogger <address to the input raw file>
* You can find an input example in the data folder


## Contributing

## License