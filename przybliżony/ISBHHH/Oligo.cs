using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ISBHHH
{
    public class OligoMeta
    {
        public Dictionary<string, int> min = new Dictionary<string,int>();
        public Dictionary<string, int> max = new Dictionary<string, int>();

        public void Add(string str, int minimum, int maximum)
        {
            min[str] = minimum;
            max[str] = maximum;
        }
    }
}
