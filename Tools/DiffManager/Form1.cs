using System;
using System.Collections;
using System.Drawing.Imaging;
using System.Windows.Forms;

namespace DiffManager
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Start_Click(object sender, EventArgs e)
        {
            var arr = new ArrayList();
            
            for (int i = 0; i < Frame.Value; i++)
                arr.Add(String.Format(Format.Text, Path.Text + "\\" + File.Text, i));
            
            var tiff = new TiffManager();
            var typey = Enum.Parse(typeof (EncoderValue), EncoderType.Text);
            tiff.JoinTiffImages(arr, String.Format("{0}.tif", File.Text), (EncoderValue)typey, (float)Ratio.Value);
            tiff.Dispose();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult res = folderBrowserDialog1.ShowDialog(this);

            if (res == DialogResult.OK)
            {
                Path.Text = folderBrowserDialog1.SelectedPath;
            }
        }
    }
}
