# ReSkel: Skeleton for Processing-in-ReRAM Synthesis
Reskel use the skeleton to represent both the computational and storage aspectives of a processing-in-ReRAM application.

Examples of ReSkel applications are demontrated in [unittest/](unittest/).
We assume the underlying architecture is a collection of ReRAM crossbars.
A crossbar operates in either the digital mode (for stateful logic) or the analog mode (for dot product or matrix-vector multiplication).

## hybrid-synthesis: a synthesis flow for the digital mode and the analog mode (multiply-and-accumulate)
* function: synthesize an application in the skeleton representation onto the target architecture with hybrid ReRAM crossbars
* compiling: ``mkdir build && cd build && cmake .. && cmake --build .``
* usage: write the application using nested skeletons in main.cpp to get its latency and bounding box
* todo: integrate the digital synthesis flow and support the analog mode

