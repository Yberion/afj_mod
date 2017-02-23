using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

//Ye all of this is ugly but whatever

namespace Bitvaluecalculator
{
    public partial class Form1 : Form
    {
        UInt64 sommeBitValue = 0u;

        public Form1()
        {
            InitializeComponent();

            //GitHub Repo
            LinkLabel.Link link_GitHub = new LinkLabel.Link();
            link_GitHub.LinkData = "https://github.com/Yberion/afjmod";
            linkLabel1.Links.Add(link_GitHub);

            //GitHub Repo
            LinkLabel.Link link_AFJ_Forum = new LinkLabel.Link();
            link_AFJ_Forum.LinkData = "http://jk-team.forum-actif.net/";
            linkLabel2.Links.Add(link_AFJ_Forum);
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 0);

            if (checkBox1.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 1);
            if (checkBox2.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 2);
            if (checkBox3.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 3);
            if (checkBox4.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox5_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 4);
            if (checkBox5.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox6_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 5);
            if (checkBox6.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox7_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 6);
            if (checkBox7.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox8_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 7);
            if (checkBox8.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox9_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 8);
            if (checkBox9.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox10_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 9);
            if (checkBox10.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox11_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 10);
            if (checkBox11.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox12_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 11);
            if (checkBox12.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox13_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 12);
            if (checkBox13.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox14_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 13);
            if (checkBox14.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox15_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 14);
            if (checkBox15.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox16_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 15);
            if (checkBox16.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox17_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 16);
            if (checkBox17.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox18_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 17);
            if (checkBox18.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox19_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 18);
            if (checkBox19.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox20_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 19);
            if (checkBox20.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox21_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 20);
            if (checkBox21.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox22_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 21);
            if (checkBox22.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox23_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 22);
            if (checkBox23.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox24_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 23);
            if (checkBox24.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox25_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 24);
            if (checkBox25.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox26_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 25);
            if (checkBox26.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox27_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 26);
            if (checkBox27.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox28_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 27);
            if (checkBox28.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox29_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 28);
            if (checkBox29.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox30_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 29);
            if (checkBox30.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox31_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 30);
            if (checkBox31.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox32_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 31);
            if (checkBox32.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox33_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 32);
            if (checkBox33.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox34_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 33);
            if (checkBox34.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox35_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 34);
            if (checkBox35.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox36_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 35);
            if (checkBox36.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox37_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 36);
            if (checkBox37.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox38_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 37);
            if (checkBox38.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox39_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 38);
            if (checkBox39.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox40_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 39);
            if (checkBox40.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void checkBox41_CheckedChanged(object sender, EventArgs e)
        {
            UInt64 checkboxVal = (UInt64)Math.Pow(2, 40);
            if (checkBox41.Checked)
            {
                sommeBitValue += checkboxVal;
            }
            else
            {
                sommeBitValue -= checkboxVal;
            }
            textBox1.Text = sommeBitValue.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            checkBox1.CheckState = CheckState.Checked;
            checkBox2.CheckState = CheckState.Checked;
            checkBox3.CheckState = CheckState.Checked;
            checkBox4.CheckState = CheckState.Checked;
            checkBox5.CheckState = CheckState.Checked;
            checkBox6.CheckState = CheckState.Checked;
            checkBox7.CheckState = CheckState.Checked;
            checkBox8.CheckState = CheckState.Checked;
            checkBox9.CheckState = CheckState.Checked;
            checkBox10.CheckState = CheckState.Checked;
            checkBox11.CheckState = CheckState.Checked;
            checkBox12.CheckState = CheckState.Checked;
            checkBox13.CheckState = CheckState.Checked;
            checkBox14.CheckState = CheckState.Checked;
            checkBox15.CheckState = CheckState.Checked;
            checkBox16.CheckState = CheckState.Checked;
            checkBox17.CheckState = CheckState.Checked;
            checkBox18.CheckState = CheckState.Checked;
            checkBox19.CheckState = CheckState.Checked;
            checkBox20.CheckState = CheckState.Checked;
            checkBox21.CheckState = CheckState.Checked;
            checkBox22.CheckState = CheckState.Checked;
            checkBox23.CheckState = CheckState.Checked;
            checkBox24.CheckState = CheckState.Checked;
            checkBox25.CheckState = CheckState.Checked;
            checkBox26.CheckState = CheckState.Checked;
            checkBox27.CheckState = CheckState.Checked;
            checkBox28.CheckState = CheckState.Checked;
            checkBox29.CheckState = CheckState.Checked;
            checkBox30.CheckState = CheckState.Checked;
            checkBox31.CheckState = CheckState.Checked;
            checkBox32.CheckState = CheckState.Checked;
            checkBox33.CheckState = CheckState.Checked;
            checkBox34.CheckState = CheckState.Checked;
            checkBox35.CheckState = CheckState.Checked;
            checkBox36.CheckState = CheckState.Checked;
            checkBox37.CheckState = CheckState.Checked;
            checkBox38.CheckState = CheckState.Checked;
            checkBox39.CheckState = CheckState.Checked;
            checkBox40.CheckState = CheckState.Checked;
            checkBox41.CheckState = CheckState.Checked;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            checkBox1.CheckState = CheckState.Unchecked;
            checkBox2.CheckState = CheckState.Unchecked;
            checkBox3.CheckState = CheckState.Unchecked;
            checkBox4.CheckState = CheckState.Unchecked;
            checkBox5.CheckState = CheckState.Unchecked;
            checkBox6.CheckState = CheckState.Unchecked;
            checkBox7.CheckState = CheckState.Unchecked;
            checkBox8.CheckState = CheckState.Unchecked;
            checkBox9.CheckState = CheckState.Unchecked;
            checkBox10.CheckState = CheckState.Unchecked;
            checkBox11.CheckState = CheckState.Unchecked;
            checkBox12.CheckState = CheckState.Unchecked;
            checkBox13.CheckState = CheckState.Unchecked;
            checkBox14.CheckState = CheckState.Unchecked;
            checkBox15.CheckState = CheckState.Unchecked;
            checkBox16.CheckState = CheckState.Unchecked;
            checkBox17.CheckState = CheckState.Unchecked;
            checkBox18.CheckState = CheckState.Unchecked;
            checkBox19.CheckState = CheckState.Unchecked;
            checkBox20.CheckState = CheckState.Unchecked;
            checkBox21.CheckState = CheckState.Unchecked;
            checkBox22.CheckState = CheckState.Unchecked;
            checkBox23.CheckState = CheckState.Unchecked;
            checkBox24.CheckState = CheckState.Unchecked;
            checkBox25.CheckState = CheckState.Unchecked;
            checkBox26.CheckState = CheckState.Unchecked;
            checkBox27.CheckState = CheckState.Unchecked;
            checkBox28.CheckState = CheckState.Unchecked;
            checkBox29.CheckState = CheckState.Unchecked;
            checkBox30.CheckState = CheckState.Unchecked;
            checkBox31.CheckState = CheckState.Unchecked;
            checkBox32.CheckState = CheckState.Unchecked;
            checkBox33.CheckState = CheckState.Unchecked;
            checkBox34.CheckState = CheckState.Unchecked;
            checkBox35.CheckState = CheckState.Unchecked;
            checkBox36.CheckState = CheckState.Unchecked;
            checkBox37.CheckState = CheckState.Unchecked;
            checkBox38.CheckState = CheckState.Unchecked;
            checkBox39.CheckState = CheckState.Unchecked;
            checkBox40.CheckState = CheckState.Unchecked;
            checkBox41.CheckState = CheckState.Unchecked;
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start(e.Link.LinkData as string);
        }

        private void linkLabel2_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start(e.Link.LinkData as string);
        }
    }
}
