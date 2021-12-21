using System;
namespace Builder
{
    public class PCSpecsBuilder : IPCBuilder
    {
        PCSpecs pcSpecs;

        public void Reset()
        {
            pcSpecs = new PCSpecs();
        }

        public PCSpecs GetResult()
        {
            return pcSpecs;
        }

        public void SetCPU(CPU cpu)
        {
            pcSpecs.cpu = cpu.Description();
        }

        public void SetGPUMemory(int memory)
        {
            pcSpecs.gpuMemory = memory;
        }

        public void SetRAMSize(int size)
        {
            pcSpecs.ramSize = size;
        }

        public void SetSSDSize(int size)
        {
            pcSpecs.ssdSize = size;
        }

        public void SetPSUPower(int power)
        {
            pcSpecs.psuPower = power;
        }
    }
}
