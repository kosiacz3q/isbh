using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace ISBHHH
{
    public static class ISBHHH
    {
        static void  Main()
        {

            CrossOligos ol = new CrossOligos();

            OligoMeta meta = new OligoMeta();


            string first = Prepare("10.in", meta);
            
            ol.GenerateMap(meta, first);

            Kontener kon = new Kontener(meta, ol);
            kon.first = first;

            kon.LiczWartosci();


            Algorytm alg = new Algorytm(kon);
            alg.Run();
        }



        public static string Prepare(string path, OligoMeta meta)
        {
            StreamReader reader = new StreamReader(path);
            reader.ReadLine();
            string first = reader.ReadLine();

            while (!reader.EndOfStream)
            {
                List<string> temp = reader.ReadLine().Split(' ').ToList();
                int type;
                int.TryParse(temp[1], out type);
                
                switch(type)
                {
                    case 1:
                        meta.min.Add(temp[0], 1);
                        meta.max.Add(temp[0], 1);
                        break;
                    case 2:
                        meta.min.Add(temp[0], 2);
                        meta.max.Add(temp[0], 3);
                        break;
                    case 3:
                        meta.min.Add(temp[0], 4);
                        meta.max.Add(temp[0], 5);
                        break;
                    case 4:
                        meta.min.Add(temp[0], 6);
                        meta.max.Add(temp[0], 9);
                        break;
                }

            }

            return first;
        }
    }
}
