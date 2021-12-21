using System;
namespace Builder
{
    public class Director
    {
        public static CPUBuilder BuilderCPU { get; set; }
        public static IPCBuilder BuilderPC { get; set; }

        // Presets

        public static void MakeHighTierCPU()
        {
            BuilderCPU.Reset();
            BuilderCPU.SetCoresCount(6);
            BuilderCPU.SetBaseFrequency(3.2f);
            BuilderCPU.SetMaxFrequency(3.6f);
            BuilderCPU.EnabledOverclocking();
        }

        public static void MakeMidTierCPU()
        {
            BuilderCPU.Reset();
            BuilderCPU.SetCoresCount(4);
            BuilderCPU.SetBaseFrequency(2.5f);
            BuilderCPU.SetMaxFrequency(3.0f);
        }

        public static void MakeGamingPC()
        {
            MakeHighTierCPU();

            BuilderPC.Reset();
            BuilderPC.SetCPU(BuilderCPU.GetResult());
            BuilderPC.SetGPUMemory(6);
            BuilderPC.SetRAMSize(16);
            BuilderPC.SetSSDSize(500);
            BuilderPC.SetPSUPower(600);
        }

        public static void MakeOfficePC()
        {
            MakeMidTierCPU();

            BuilderPC.Reset();
            BuilderPC.SetCPU(BuilderCPU.GetResult());
            BuilderPC.SetGPUMemory(1);
            BuilderPC.SetRAMSize(8);
            BuilderPC.SetSSDSize(250);
            BuilderPC.SetPSUPower(300);
        }

    }
}
