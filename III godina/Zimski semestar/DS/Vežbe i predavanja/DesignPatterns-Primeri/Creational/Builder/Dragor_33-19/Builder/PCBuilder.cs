using System;
namespace Builder
{
    public class PCBuilder : IPCBuilder
    {
        PC pc;

        public void Reset()
        {
            pc = new PC();
        }

        public PC GetResult()
        {
            return pc;
        }

        public void SetCPU(CPU cpu)
        {
            pc.cpu = cpu;
        }

        public void SetGPUMemory(int memory)
        {
            pc.gpuMemory = memory;
        }

        public void SetRAMSize(int size)
        {
            pc.ramSize = size;
        }

        public void SetSSDSize(int size)
        {
            pc.ssdSize = size;
        }

        public void SetPSUPower(int power)
        {
            pc.psuPower = power;
        }
    }
}
