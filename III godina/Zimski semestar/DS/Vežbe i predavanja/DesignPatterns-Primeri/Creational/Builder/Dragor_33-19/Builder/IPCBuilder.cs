using System;
namespace Builder
{
    public interface IPCBuilder
    {
        void Reset();
        void SetCPU(CPU cpu);
        void SetGPUMemory(int memory);
        void SetRAMSize(int size);
        void SetSSDSize(int size);
        void SetPSUPower(int power);
    }
}
