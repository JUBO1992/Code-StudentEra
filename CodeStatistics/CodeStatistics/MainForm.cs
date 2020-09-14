using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Threading;

namespace CodeStatistics
{
    public partial class MainForm : Form
    {
        public String m_CodePath = null;
        public List<CodeFilePro> m_CodeFileList = new List<CodeFilePro>();
        public bool m_IsCountEnd = false;
        public MainForm()
        {
            InitializeComponent();
        }

        private void btnScanFolder_Click(object sender, EventArgs exter)
        {
            FolderBrowserDialog FolderDialog = new FolderBrowserDialog();
            FolderDialog.ShowNewFolderButton = false;
            if (FolderDialog.ShowDialog() == DialogResult.OK)
            {
                m_CodePath = FolderDialog.SelectedPath;
                txtCodePath.Text = m_CodePath;
            }
            else
                return;
            m_CodeFileList.Clear();
            DirectoryInfo dir = new DirectoryInfo(m_CodePath);
            FileInfo[] finfo;
            List<String> extension = new List<String>();
            extension.Add("*.cs");
            extension.Add("*.c");
            extension.Add("*.h");
            extension.Add("*.cpp");
            foreach (String ext in extension)
            {
                finfo = dir.GetFiles(ext, SearchOption.AllDirectories);//递归搜索
                for (int i = 0; i < finfo.Length; i++)
                {
                    CodeFilePro temp = new CodeFilePro();
                    String fpath = finfo[i].FullName;
                    temp.FilePath = fpath;
                    String fname = Path.GetFileName(fpath);
                    temp.FileName = fname;
                    m_CodeFileList.Add(temp);
                }
            }
            UpdateView(false);
        }

        private void UpdateView(bool flag)
        {
            //listView1.Clear();
            //listView1.Columns.Add("序号", 40, HorizontalAlignment.Left);
            //listView1.Columns.Add("文件名", 100, HorizontalAlignment.Left);
            //listView1.Columns.Add("文件路径", 200, HorizontalAlignment.Left);
            //listView1.Columns.Add("总行数", 60, HorizontalAlignment.Center);
            //listView1.Columns.Add("代码行", 60, HorizontalAlignment.Center);
            //listView1.Columns.Add("注释行", 60, HorizontalAlignment.Center);
            //listView1.Columns.Add("空白行", 60, HorizontalAlignment.Center);
            listView1.Items.Clear();//清除所有项
            for (int i = 0; i < m_CodeFileList.Count; i++)
            {
                ListViewItem lvItem = new ListViewItem((i+1).ToString());
                lvItem.SubItems.Add(m_CodeFileList[i].FileName);
                lvItem.SubItems.Add(m_CodeFileList[i].FilePath);
                if (flag == true)
                {
                    lvItem.SubItems.Add(m_CodeFileList[i].TotalLines.ToString());
                    lvItem.SubItems.Add(m_CodeFileList[i].CodeLines.ToString());
                    lvItem.SubItems.Add(m_CodeFileList[i].NoteLines.ToString());
                    lvItem.SubItems.Add(m_CodeFileList[i].BlankLines.ToString());
                }
                listView1.Items.Add(lvItem);
            }
            listView1.Update();
        }
        
        public void Read(string path, CodeFilePro cfproperty)
        {
            int tlines = 0, clines = 0, nlines = 0, blines = 0;
            StreamReader sr = new StreamReader(path, Encoding.Default);
            String line;
            bool noteflag = false;//遇见/*noteflag=true 遇到*/noteflag=false
            while ((line = sr.ReadLine()) != null)
            {
                tlines++;
                line = line.Trim();
                if (String.IsNullOrEmpty(line))
                    blines++;
                else
                {
                    if (noteflag == true)
                    {
                        if (line.EndsWith("*/"))
                        {
                            noteflag = false;
                            nlines++;
                        }
                        else
                        {
                            if (line.Contains("*///"))
                            {
                                noteflag = false;
                                nlines++;
                            }
                            else if (line.Contains("*/"))
                            {
                                noteflag = false;
                                clines++;
                            }
                            else
                                nlines++;
                        }
                    }
                    else//notefalg == flase
                    {
                        if (line.StartsWith("//"))
                            nlines++;
                        else
                        {
                            if (line.StartsWith("/*"))
                            {
                                if (line.EndsWith("*/"))
                                {
                                    nlines++;
                                }
                                else if (line.Contains("*///"))
                                {
                                    nlines++;
                                }
                                else if (line.Contains("*/"))
                                {
                                    clines++;
                                }
                                else
                                {
                                    noteflag = true;
                                    nlines++;
                                }
                            }
                            else
                            {
                                /*特殊情况该如何处理？如何判断“/*”是否有效？
                                 ...".../*...\"\"\"..."/*
                                 /*
                                */
                                if (line.Contains("/*"))//设置判断/*有效的条件
                                {
                                    if (line.Contains("*/"))// */应该在/*之后
                                    {
                                        clines++;
                                    }
                                    else
                                    {
                                        noteflag = true;
                                        clines++;
                                    }
                                }
                                else
                                    clines++;
                            }
                        }
                    }
                }
            }
            cfproperty.TotalLines = tlines;
            cfproperty.CodeLines = clines;
            cfproperty.NoteLines = nlines;
            cfproperty.BlankLines = blines;
        }

        private void btnCountE_Click(object sender, EventArgs e)
        {
            Thread t = new Thread(CountLines);
            t.IsBackground = true;
            t.Start();
            timer1.Start();
        }

        public void CountLines()
        {
            for (int i = 0; i < m_CodeFileList.Count; i++)
            {
                Read(m_CodeFileList[i].FilePath, m_CodeFileList[i]);
            }
            m_IsCountEnd = true;
        }

        private void btnCountA_Click(object sender, EventArgs e)
        {
            int tlines = 0, clines = 0, nlines = 0, blines = 0;
            for (int i = 0; i < m_CodeFileList.Count; i++)
            {
                tlines += m_CodeFileList[i].TotalLines;
                clines += m_CodeFileList[i].CodeLines;
                nlines += m_CodeFileList[i].NoteLines;
                blines += m_CodeFileList[i].BlankLines;
            }
            txtTotalLines.Text = tlines.ToString();
            txtCodeLines.Text = clines.ToString();
            txtNoteLines.Text = nlines.ToString();
            txtBlankLines.Text = blines.ToString();
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            listView1.Items.Clear();
            txtTotalLines.Text = "";
            txtCodeLines.Text = "";
            txtNoteLines.Text = "";
            txtBlankLines.Text = "";
        }

        private void listView1_SizeChanged(object sender, EventArgs e)
        {
            int listwidth = listView1.Size.Width;
            if (listwidth >= 612)
            {
                listView1.Columns[0].Width = (int)(40.0 / 612 * listwidth);
                listView1.Columns[1].Width = (int)(100.0 / 612 * listwidth);
                listView1.Columns[2].Width = (int)(200.0 / 612 * listwidth);
                listView1.Columns[3].Width = (int)(60.0 / 612 * listwidth);
                listView1.Columns[4].Width = (int)(60.0 / 612 * listwidth);
                listView1.Columns[5].Width = (int)(60.0 / 612 * listwidth);
                listView1.Columns[6].Width = (int)(60.0 / 612 * listwidth);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (m_IsCountEnd == true)
            {
                UpdateView(true);
                timer1.Stop();
            }
        }
    }
}
