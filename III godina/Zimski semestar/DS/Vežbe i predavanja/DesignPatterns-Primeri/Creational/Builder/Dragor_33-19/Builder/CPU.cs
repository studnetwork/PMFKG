using System;
namespace Builder
{
    public class CPU
    {
        public int coresCount;
        public float baseFrequency;
        public float maxFrequency;
        public bool ableToOverclock;

        public string Description()
        {
            return "Processor with " + coresCount + " cores and frequency range from " + baseFrequency + "GHz (base) to " + maxFrequency + "GHz (peek).";
        }

        public override string ToString()
        {
            return coresCount + " cores | base freq. " + baseFrequency + "GHz | max freq. " + maxFrequency + "GHz";
        }
    }
}
