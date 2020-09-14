using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace RenameFiles
{
    public partial class MainForm : Form
    {
        public List<String> m_FileList = new List<String>();//原始文件路径列表
        public List<String> m_NFileList = new List<String>();//新文件名列表
        public bool m_IsAutoPreview = true;//自动预览开关
        public int m_CurrentModel = 0;//当前选项卡index
        public MainForm()
        {
            InitializeComponent();
        }

        private void btnOpenFiles_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Multiselect = true;
            if (dlg.ShowDialog() != DialogResult.OK)
                return;
            String[] filelist = dlg.FileNames;
            foreach (string file in filelist)
            {
                if (!m_FileList.Contains(file))
                    m_FileList.Add(file);
            }
            UpdateView();
            UpdateNfileList();
        }

        private void btnOpenFolder_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog FolderDialog = new FolderBrowserDialog();
            FolderDialog.ShowNewFolderButton = false;
            if (FolderDialog.ShowDialog() != DialogResult.OK)
                return;
            DirectoryInfo dir = new DirectoryInfo(FolderDialog.SelectedPath);
            FileInfo[] finfo = dir.GetFiles();
            foreach (FileInfo ff in finfo)
            {
                if (!m_FileList.Contains(ff.FullName) && ff.Attributes != FileAttributes.Hidden)
                    m_FileList.Add(ff.FullName);
            }
            UpdateView();
            UpdateNfileList();
        }

        private void btnClearAll_Click(object sender, EventArgs e)
        {
            m_FileList.Clear();
            UpdateView();
        }

        private void UpdateView()
        {
            listView1.Items.Clear();
            for (int i = 0; i < m_FileList.Count; i++)
            {
                ListViewItem lvItem = new ListViewItem((i + 1).ToString());
                lvItem.SubItems.Add(Path.GetFileName(m_FileList[i]));
                lvItem.SubItems.Add("");
                lvItem.SubItems.Add(m_FileList[i]);
                listView1.Items.Add(lvItem);
            }
            listView1.Update();
        }

        private void Textbox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == '\\' || e.KeyChar == '/' || e.KeyChar == ':' || e.KeyChar == '*' || e.KeyChar == '?'
                 || e.KeyChar == '<' || e.KeyChar == '>' || e.KeyChar == '"' || e.KeyChar == '|')
            {
                    e.Handled = true;
            }
        }

        private void UpdateNfileList()
        {
            if (m_CurrentModel == 0)
                CommonRename();
            else if (m_CurrentModel == 1)
                ReplaceRename();
            else if (m_CurrentModel == 2)
                InsertRename();
            else if (m_CurrentModel == 3)
                ToUpperLowerRename();
        }
        private void btnPreview_Click(object sender, EventArgs e)
        {
            UpdateNfileList();
        }

        /// <summary>
        /// 控件值改变时触发刷新listView中的新文件名
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Control_ValueChanged(object sender, EventArgs e)
        {
            if (!m_IsAutoPreview)
                return;
            UpdateNfileList();
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_CurrentModel = tabControl1.SelectedIndex;
            UpdateNfileList();
        }

        private void btnAutoPreview_Click(object sender, EventArgs e)
        {
            m_IsAutoPreview = !m_IsAutoPreview;
            if (m_IsAutoPreview)
            {
                btnPreview.Enabled = false;
                btnAutoPreview.BackgroundImage = RenameFiles.Properties.Resources.autopreview;
            }
            else
            {
                btnPreview.Enabled = true;
                btnAutoPreview.BackgroundImage = RenameFiles.Properties.Resources.stoppreview;
            }
        }

        private void CommonRename()//常规重命名
        {
            m_NFileList.Clear();
            for (int i = 0; i < m_FileList.Count; i++)
            {
                String str = txtFilePrefix.Text
                    + txtFileMian.Text
                    + String.Format("{0:D" + numericFileNo.Value + "}", (int)(numericStartNo.Value + i * numericIncrement.Value))
                    + txtFileSuffix.Text
                    +Path.GetExtension(m_FileList[i]);
                m_NFileList.Add(str);
            }
            for (int i = 0; i < listView1.Items.Count; i++)
            {
                listView1.Items[i].SubItems[2].Text = m_NFileList[i];
            }
        }

        private void ReplaceRename()//替换重命名
        {
            if (String.IsNullOrEmpty(txtSearchContent.Text))
            {
                m_NFileList.Clear();
                for (int i = 0; i < m_FileList.Count; i++)
                {
                    String file = Path.GetFileName(m_FileList[i]);
                    m_NFileList.Add(file);
                }
                for (int i = 0; i < listView1.Items.Count; i++)
                {
                    listView1.Items[i].SubItems[2].Text = m_NFileList[i];
                }
               return;
            }
            m_NFileList.Clear();
            for (int i = 0; i < m_FileList.Count; i++)
            {
                String file = Path.GetFileName(m_FileList[i]);
                String str = null;
                if (chBoxIsSensitive.Checked)
                {
                    //method1
                    //str = file.Replace(txtSearchContent.Text, txtReplaceContent.Text);
                    //method2
                    int length = txtSearchContent.Text.Length;
                    int pos = file.IndexOf(txtSearchContent.Text, StringComparison.Ordinal);
                    if (pos >= 0)
                    {
                        file = file.Remove(pos, length);
                        file = file.Insert(pos, txtReplaceContent.Text);
                    }
                    str = file;
                }
                else
                {
                    int length = txtSearchContent.Text.Length;
                    int pos = file.IndexOf(txtSearchContent.Text, StringComparison.OrdinalIgnoreCase);
                    if (pos >= 0)
                    {
                        file = file.Remove(pos, length);
                        file = file.Insert(pos, txtReplaceContent.Text);
                    }
                    str = file;
                }
                m_NFileList.Add(str);
            }
            for (int i = 0; i < listView1.Items.Count; i++)
            {
                listView1.Items[i].SubItems[2].Text = m_NFileList[i];
            }
        }

        private void InsertRename()//插入重命名
        {
            m_NFileList.Clear();
            for (int i = 0; i < m_FileList.Count; i++)
            {
                String file = Path.GetFileName(m_FileList[i]);
                int pos = (int)numericInsertPos.Value > file.Length ? file.Length : (int)numericInsertPos.Value;
                if(!radBtnStartPos.Checked)
                    pos = file.Length - pos;
                String str = file.Insert(pos, txtInsertContent.Text);
                m_NFileList.Add(str);
            }
            for (int i = 0; i < listView1.Items.Count; i++)
            {
                listView1.Items[i].SubItems[2].Text = m_NFileList[i];
            }
        }

        private void ToUpperLowerRename()
        {
            m_NFileList.Clear();
            for (int i = 0; i < m_FileList.Count; i++)
            {
                String file = Path.GetFileNameWithoutExtension(m_FileList[i]);
                String extension = Path.GetExtension(m_FileList[i]);
                if (radBtnFToLower.Checked)
                    file = file.ToLower();
                else if (radBtnFToUpper.Checked)
                    file = file.ToUpper();
                else if (radBtnFWToUpper.Checked)
                {
                    file = file.Substring(0,1).ToUpper() + file.Substring(1);
                }
                else if (radBtnFWToLower.Checked)
                {
                    file = file.Substring(0, 1).ToLower() + file.Substring(1);
                }

                if (radBtnEToLower.Checked)
                    extension = extension.ToLower();
                else if (radBtnEToUpper.Checked)
                    extension = extension.ToUpper();
                String str = file + extension;
                m_NFileList.Add(str);
            }
            for (int i = 0; i < listView1.Items.Count; i++)
            {
                listView1.Items[i].SubItems[2].Text = m_NFileList[i];
            }
        }

        public List<String> m_CFList = new List<String>();//修改前文件名列表拷贝
        public List<String> m_CNList = new List<String>();//修改后文件名列表拷贝
        private void btnRun_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < m_FileList.Count;i ++ )
            {
                String nfile = Path.GetDirectoryName(m_FileList[i]) + "\\" + m_NFileList[i];
                File.Move(m_FileList[i], nfile);
            }
            m_CFList.Clear(); m_CNList.Clear();
            m_CFList = new List<String>(m_FileList.ToArray());
            m_CNList = new List<String>(m_NFileList.ToArray());
            btnUndo.Enabled = true;
            MessageBox.Show("Done!");
            m_FileList.Clear(); m_NFileList.Clear();
            UpdateView();
        }

        private void btnUndo_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < m_CNList.Count; i++)
            {
                String nfile = Path.GetDirectoryName(m_CFList[i]) + "\\" + m_CNList[i];
                File.Move(nfile, m_CFList[i]);
            }
            btnUndo.Enabled = false;
            btnRedo.Enabled = true;
            MessageBox.Show("Done!");
        }

        private void btnRedo_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < m_CNList.Count; i++)
            {
                String nfile = Path.GetDirectoryName(m_CFList[i]) + "\\" + m_CNList[i];
                File.Move(m_CFList[i], nfile);
            }
            btnUndo.Enabled = true;
            btnRedo.Enabled = false;
            MessageBox.Show("Done!");
        }

        private void listView1_Resize(object sender, EventArgs e)
        {
            int listwidth = listView1.Size.Width;
            if (listwidth >= 613)
            {
                listView1.Columns[0].Width = (int)(40.0 / 613 * listwidth);
                listView1.Columns[1].Width = (int)(150.0 / 613 * listwidth);
                listView1.Columns[2].Width = (int)(150.0 / 613 * listwidth);
                listView1.Columns[3].Width = (int)(220.0 / 613 * listwidth);
            }
        }
    }
}
