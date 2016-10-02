using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ISBHHH
{
    public class Kontener
    {

        public List<string> wartosci;
        public List<string> sprawdzone;
        public List<string> kolejka;
        public string first;
        private int dlugoscWszystkich;

        public Kontener() { }

        CrossOligos cross;

        public Kontener(Kontener old)
        {
            this.wartosci = old.wartosci.Select(item => (string)item.Clone()).ToList();
            this.cross = old.cross;
            this.first = old.first;
            this.LiczWartosci();
        }

        public Kontener(OligoMeta meta, CrossOligos cr)
        {
            cross = cr;
            wartosci = new List<string>();
            sprawdzone = new List<string>();

            foreach (var x in meta.max)
                wartosci.Add(String.Copy(x.Key));

            wartosci = wartosci.OrderBy(a => Guid.NewGuid()).ToList();
        }

        public Kontener insert(int from, int to)
        {
            Kontener result = new Kontener(this);

            string temp = result.wartosci[from];
            result.wartosci.RemoveAt(from);
            result.wartosci.Insert(to, temp);

            return result;
        }

        public int Test()
        {
            int temp = dlugoscWszystkich;
            for (int i = 0; i < wartosci.Count; i++ )
            {
                if (i - 1 < 0)
                    temp -= cross.map[first][wartosci[i]].Max();
                else
                    temp -= cross.map[wartosci[i - 1]][wartosci[i]].Max();
            }

            return temp;
        }
        
        public void LiczWartosci()
        {
            dlugoscWszystkich = wartosci.Select(x => x.Count()).Sum();
        }

        public string Result()
        {
            string result = first;
            for (int i = 0; i < wartosci.Count; i++)
            {
                if (i == 0)
                    result += wartosci[i].Substring(cross.map[first][wartosci[i]].Max());
                else
                    result += wartosci[i].Substring(cross.map[wartosci[i - 1]][wartosci[i]].Max());
            }

            return result;
        }

    }
}
