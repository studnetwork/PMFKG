using System;
namespace Builder
{
    public class CPUBuilder
    {
        CPU cpu;

        public void Reset()
        {
            cpu = new CPU();
        }

        public CPU GetResult()
        {
            return cpu;
        }

        public void SetCoresCount(int count)
        {
            cpu.coresCount = count;
        }

        public void SetBaseFrequency(float freq)
        {
            cpu.baseFrequency = freq;
        }

        public void SetMaxFrequency(float freq)
        {
            cpu.maxFrequency = freq;
        }

        public void EnabledOverclocking()
        {
            cpu.ableToOverclock = true;
        }
    }
}
