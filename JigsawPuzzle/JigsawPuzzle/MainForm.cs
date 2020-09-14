using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace JigsawPuzzle
{
    public partial class MainForm : Form
    {
        public List<int> m_RadomList = new List<int>();
        public int m_Time = 0;
        public int m_Move = 0;
        public bool m_StartCount = false;//开始计时标志
        public MainForm()
        {
            InitializeComponent();
            //Init List
            for (int i = 0; i < 16; i++)
                m_RadomList.Add(i + 1);
            //m_RadomList = InitList();
            InitView();
            UpdateButtonView();
            timer1.Start();
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (m_StartCount == false)
            {
                if (keyData == Keys.Up || keyData == Keys.Down ||
                    keyData == Keys.Left || keyData == Keys.Right ||
                    keyData == Keys.W || keyData == Keys.S ||
                    keyData == Keys.A || keyData == Keys.D)
                {
                    m_StartCount = true;
                }
            }
            int n = m_RadomList.IndexOf(16);
            switch (keyData)
            {
                case Keys.F1:
                    MessageBox.Show("F1");
                    break;
                case Keys.W:
                case Keys.Down:
                    if (n - 4 >= 0)
                    {
                        m_Move++;
                        textBox2.Text = m_Move.ToString();
                        m_RadomList[n] = m_RadomList[n - 4];
                        m_RadomList[n - 4] = 16;
                    }
                    break;
                case Keys.S:
                case Keys.Up:
                    if (n + 4 < 16)
                    {
                        m_Move++;
                        textBox2.Text = m_Move.ToString();
                        m_RadomList[n] = m_RadomList[n + 4];
                        m_RadomList[n + 4] = 16;
                    }
                    break;
                case Keys.A:
                case Keys.Right:
                    if (n % 4 != 0)
                    {
                        m_Move++;
                        textBox2.Text = m_Move.ToString();
                        m_RadomList[n] = m_RadomList[n - 1];
                        m_RadomList[n - 1] = 16;
                    }
                    break;
                case Keys.D:
                case Keys.Left:
                    if (n % 4 != 3)
                    {
                        m_Move++;
                        textBox2.Text = m_Move.ToString();
                        m_RadomList[n] = m_RadomList[n + 1];
                        m_RadomList[n + 1] = 16;
                    }
                    break;
            }
            UpdateButtonView();
            if (GetResult() == true)
            {
                timer1.Stop();
                m_StartCount = false;
                MessageBox.Show("You Win!\nGood for You!");
            }
            return true;
            return base.ProcessCmdKey(ref msg, keyData);
        }

        private List<int> InitList()
        {
            Random rd = new Random();
            List<int> list = new List<int>();
            for (int i = 0; i < 16; i++)
                list.Add(i + 1);
            int temp = 0, k = 0;
            //for (int i = 0; i < 2; i++)
            //{
            //    for (int j = 0; j < list.Count; j++)
            //    {
            //        k = rd.Next(16);
            //        temp = list[j];
            //        list[j] = list[k];
            //        list[k] = temp;
            //    }
            //}
            //做25次三轮转
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 15; j+=3)
                {
                    int a = rd.Next(0, 16);
                    int b = rd.Next(0, 16);
                    int c = rd.Next(0, 16);
                    temp = list[a];
                    list[a] = list[b];
                    list[b] = list[c];
                    list[c] = temp;
                }
            }
            return list;
        }

        private void InitView()
        {
            //随机走200步
            Random rd = new Random();
            for (int i = 0; i < 200; i++)
            {
                int n = m_RadomList.IndexOf(16);
                switch (rd.Next(4))
                {
                    case 0:
                        if (n - 4 >= 0)
                        {
                            m_RadomList[n] = m_RadomList[n - 4];
                            m_RadomList[n - 4] = 16;
                        }
                        break;
                    case 1:
                        if (n + 4 < 16)
                        {
                            m_RadomList[n] = m_RadomList[n + 4];
                            m_RadomList[n + 4] = 16;
                        }
                        break;
                    case 2:
                        if (n % 4 != 0)
                        {
                            m_RadomList[n] = m_RadomList[n - 1];
                            m_RadomList[n - 1] = 16;
                        }
                        break;
                    case 3:
                        if (n % 4 != 3)
                        {
                            m_RadomList[n] = m_RadomList[n + 1];
                            m_RadomList[n + 1] = 16;
                        }
                        break;
                }
            }
        }

        private void btnStartOver_Click(object sender, EventArgs e)
        {
            //m_RadomList = InitList();
            InitView();
            UpdateButtonView();
            m_Time = 0;
            textBox1.Text = "0";
            m_Move = 0;
            textBox2.Text = "0";
            timer1.Start();
        }

        private void UpdateButtonView()
        {
            button1.Text = m_RadomList[0] == 16 ? "" : m_RadomList[0].ToString();
            button2.Text = m_RadomList[1] == 16 ? "" : m_RadomList[1].ToString();
            button3.Text = m_RadomList[2] == 16 ? "" : m_RadomList[2].ToString();
            button4.Text = m_RadomList[3] == 16 ? "" : m_RadomList[3].ToString();
            button5.Text = m_RadomList[4] == 16 ? "" : m_RadomList[4].ToString();
            button6.Text = m_RadomList[5] == 16 ? "" : m_RadomList[5].ToString();
            button7.Text = m_RadomList[6] == 16 ? "" : m_RadomList[6].ToString();
            button8.Text = m_RadomList[7] == 16 ? "" : m_RadomList[7].ToString();
            button9.Text = m_RadomList[8] == 16 ? "" : m_RadomList[8].ToString();
            button10.Text = m_RadomList[9] == 16 ? "" : m_RadomList[9].ToString();
            button11.Text = m_RadomList[10] == 16 ? "" : m_RadomList[10].ToString();
            button12.Text = m_RadomList[11] == 16 ? "" : m_RadomList[11].ToString();
            button13.Text = m_RadomList[12] == 16 ? "" : m_RadomList[12].ToString();
            button14.Text = m_RadomList[13] == 16 ? "" : m_RadomList[13].ToString();
            button15.Text = m_RadomList[14] == 16 ? "" : m_RadomList[14].ToString();
            button16.Text = m_RadomList[15] == 16 ? "" : m_RadomList[15].ToString();
        }

        private bool GetResult()
        {
            for (int i = 0; i < 16; i++)
            {
                if (m_RadomList[i] != i + 1)
                    return false;
            }
            return true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (m_StartCount)
            {
                m_Time++;
                textBox1.Text = m_Time.ToString();
            }
        }
    }
}
