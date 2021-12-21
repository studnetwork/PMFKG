using System;
using System.Collections.Generic;

namespace Builder
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            // > Create Builders 
            PCSpecsBuilder pcBuilder = new PCSpecsBuilder();
            //PCBuilder pcBuilder = new PCBuilder();
            CPUBuilder cpuBuilder = new CPUBuilder();

            // > Set Directors Builders
            Director.BuilderPC = pcBuilder;
            Director.BuilderCPU = cpuBuilder;

            // > Create Products
            Director.MakeGamingPC();
            Console.WriteLine(pcBuilder.GetResult());
            Director.MakeOfficePC();
            Console.WriteLine(pcBuilder.GetResult());
        }
    }
}
