using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ISBHHH
{
    public class CrossOligos
    {
        public Dictionary<string, Dictionary<string, List<int>>> map;

        public CrossOligos()
        {
            map = new Dictionary<string, Dictionary<string, List<int>>>();
        }

        public void GenerateMap(OligoMeta list, string first)
        {

            foreach (var l in list.min)
            {
                foreach (var k in list.max)
                {
                    List<int> eval = new List<int>();
                    eval = Evaluate(l.Key, k.Key);
                    if (!map.ContainsKey(l.Key))
                        map[l.Key] = new Dictionary<string, List<int>>() { { k.Key, eval } };
                    else
                        map[l.Key].Add(k.Key, eval);
                }
            }

            list.min.Remove(first);
            list.max.Remove(first);

        }

        public List<int> Evaluate(string arg1, string arg2)
        {
            int l1 = arg1.Count();
            int l2 = arg2.Count();

            List<int> reached = new List<int>() { 0 };

            for (int i = 1; i <= l1 && i <= l2; i++)
            {
                string temp1 = arg1.Substring(l1 - i);
                string temp2 = arg2.Substring(0, i);

                if (temp1 == temp2)
                    reached.Add(temp1.Count());
            }
            return reached;
        }
    }
}
