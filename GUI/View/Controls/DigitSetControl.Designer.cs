namespace GUI.View.Controls
{
	partial class DigitSetControl
	{
		/// <summary> 
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary> 
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Component Designer generated code

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.loadDigitFileButton = new System.Windows.Forms.Button();
			this.loadLabelFileButton = new System.Windows.Forms.Button();
			this.digitFileNameLabel = new System.Windows.Forms.Label();
			this.labelFileNameLabel = new System.Windows.Forms.Label();
			this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
			this.loadDigitSetButton = new System.Windows.Forms.Button();
			this.digitSetSizeLabel = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// loadDigitFileButton
			// 
			this.loadDigitFileButton.Location = new System.Drawing.Point(3, 3);
			this.loadDigitFileButton.Name = "loadDigitFileButton";
			this.loadDigitFileButton.Size = new System.Drawing.Size(102, 23);
			this.loadDigitFileButton.TabIndex = 0;
			this.loadDigitFileButton.Text = "Load digit file";
			this.loadDigitFileButton.UseVisualStyleBackColor = true;
			this.loadDigitFileButton.Click += new System.EventHandler(this.LoadDigitFileButtonClick);
			// 
			// loadLabelFileButton
			// 
			this.loadLabelFileButton.Location = new System.Drawing.Point(3, 32);
			this.loadLabelFileButton.Name = "loadLabelFileButton";
			this.loadLabelFileButton.Size = new System.Drawing.Size(102, 23);
			this.loadLabelFileButton.TabIndex = 1;
			this.loadLabelFileButton.Text = "Load label file";
			this.loadLabelFileButton.UseVisualStyleBackColor = true;
			this.loadLabelFileButton.Click += new System.EventHandler(this.LoadLabelFileButtonClick);
			// 
			// digitFileNameLabel
			// 
			this.digitFileNameLabel.AutoSize = true;
			this.digitFileNameLabel.Location = new System.Drawing.Point(111, 8);
			this.digitFileNameLabel.Name = "digitFileNameLabel";
			this.digitFileNameLabel.Size = new System.Drawing.Size(0, 13);
			this.digitFileNameLabel.TabIndex = 2;
			// 
			// labelFileNameLabel
			// 
			this.labelFileNameLabel.AutoSize = true;
			this.labelFileNameLabel.Location = new System.Drawing.Point(111, 37);
			this.labelFileNameLabel.Name = "labelFileNameLabel";
			this.labelFileNameLabel.Size = new System.Drawing.Size(0, 13);
			this.labelFileNameLabel.TabIndex = 3;
			// 
			// openFileDialog
			// 
			this.openFileDialog.Filter = "All files|*.*";
			// 
			// loadDigitSetButton
			// 
			this.loadDigitSetButton.Location = new System.Drawing.Point(4, 62);
			this.loadDigitSetButton.Name = "loadDigitSetButton";
			this.loadDigitSetButton.Size = new System.Drawing.Size(101, 23);
			this.loadDigitSetButton.TabIndex = 4;
			this.loadDigitSetButton.Text = "Load digit set";
			this.loadDigitSetButton.UseVisualStyleBackColor = true;
			this.loadDigitSetButton.Click += new System.EventHandler(this.LoadDigitSetButtonClick);
			// 
			// digitSetSizeLabel
			// 
			this.digitSetSizeLabel.AutoSize = true;
			this.digitSetSizeLabel.Location = new System.Drawing.Point(111, 67);
			this.digitSetSizeLabel.Name = "digitSetSizeLabel";
			this.digitSetSizeLabel.Size = new System.Drawing.Size(0, 13);
			this.digitSetSizeLabel.TabIndex = 5;
			// 
			// DigitSetControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.AutoSize = true;
			this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.Controls.Add(this.digitSetSizeLabel);
			this.Controls.Add(this.loadDigitSetButton);
			this.Controls.Add(this.labelFileNameLabel);
			this.Controls.Add(this.digitFileNameLabel);
			this.Controls.Add(this.loadLabelFileButton);
			this.Controls.Add(this.loadDigitFileButton);
			this.Name = "DigitSetControl";
			this.Size = new System.Drawing.Size(114, 88);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button loadDigitFileButton;
		private System.Windows.Forms.Button loadLabelFileButton;
		private System.Windows.Forms.Label digitFileNameLabel;
		private System.Windows.Forms.Label labelFileNameLabel;
		private System.Windows.Forms.OpenFileDialog openFileDialog;
		private System.Windows.Forms.Button loadDigitSetButton;
		private System.Windows.Forms.Label digitSetSizeLabel;
	}
}
