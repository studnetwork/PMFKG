using System;
namespace Builder
{
    public class PCSpecs
    {
        // Set by Builder
        public string cpu;
        public int gpuMemory;
        public int ramSize;
        public int ssdSize;
        public int psuPower;

        public override string ToString()
        {
            return "PC Specs\n + CPU: " + cpu + "\n + GPU: " + gpuMemory + "GB\n + RAM: " + ramSize + "GB\n + SSD: " + ssdSize + "GB\n + PSU: " + psuPower + "W";
        }
    }
}
