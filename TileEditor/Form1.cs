using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TileEditor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Bitmap bMap = new Bitmap("key.png");
            pictureBox1.Image = bMap;
            
            //FileStream fStream = new FileStream("key.png", FileMode.Open);
        }
    }
}
