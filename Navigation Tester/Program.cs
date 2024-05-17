using Navigation_Tester.Common;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Net.Mime.MediaTypeNames;

namespace Navigation_Tester
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("App started");
            Loader.Load();

            uint mapId = 0;
            //new Vector3(-8902.59f, -162.606f, 81.93913f),
            //new Vector3(-8945.741f, -129.6458f, 83.56361f),
            var player = new Vector3(-8897.289f, -173.7151f, 81.57756f);
            var target = new Vector3(-8902.13f, -181.646f, 113.1567f); 
           

            var results = Loader.CalculatePath(mapId, player, target).Count();




            Console.WriteLine("App Completed");
            Console.Read();
        }
    }
}
