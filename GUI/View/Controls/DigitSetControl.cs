using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI.View.Controls
{
	/// <summary>
	/// Control used to load digit set
	/// </summary>
	public partial class DigitSetControl : UserControl
	{
		/// <summary>
		/// Invoked when user decides to load digit set
		/// </summary>
		/// <param name="digitFilePath"></param>
		/// <param name="labelFilePath"></param>
		public delegate void LoadDigitSetDelegate(string digitFilePath, string labelFilePath);

		private string digitFileName, labelFileName;
		public LoadDigitSetDelegate LoadDigitSet;

		/// <summary>
		/// Allows to show loaded digit set size
		/// </summary>
		public uint DigitSetSize
		{
			set
			{
				digitSetSizeLabel.Text = "Size: " + value;
			}
		}

		public DigitSetControl()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Event handler for loading digit set from files
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="eventArgs"></param>
		private void LoadDigitSetButtonClick(object sender, EventArgs eventArgs)
		{
			if(labelFileName != "" && digitFileName != "" && labelFileName != null && digitFileName != null)
			{
				LoadDigitSet?.Invoke(digitFileName, labelFileName);
			}
			else
			{
				MessageBox.Show("Please open both files");
			}
		}

		/// <summary>
		/// Event handler for opening digit file
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="eventArgs"></param>
		private void LoadDigitFileButtonClick(object sender, EventArgs eventArgs)
		{
			if(openFileDialog.ShowDialog() == DialogResult.OK)
			{
				digitFileNameLabel.Text = digitFileName = openFileDialog.FileName;
			}
		}

		/// <summary>
		/// Event handler for opening label file
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="eventArgs"></param>
		private void LoadLabelFileButtonClick(object sender, EventArgs eventArgs)
		{
			if (openFileDialog.ShowDialog() == DialogResult.OK)
			{
				labelFileNameLabel.Text = labelFileName = openFileDialog.FileName;
			}
		}
	}
}
