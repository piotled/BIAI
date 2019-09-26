namespace GUI.Controls
{
	partial class NeuralNetworkControl
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
			this.loadNetworkButton = new System.Windows.Forms.Button();
			this.saveNetworkButton = new System.Windows.Forms.Button();
			this.createNetworkButton = new System.Windows.Forms.Button();
			this.networkFormatTextBox = new System.Windows.Forms.TextBox();
			this.networkOpenFileDialog = new System.Windows.Forms.OpenFileDialog();
			this.networkSaveFileDialog = new System.Windows.Forms.SaveFileDialog();
			this.clearButton = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// loadNetworkButton
			// 
			this.loadNetworkButton.Location = new System.Drawing.Point(4, 4);
			this.loadNetworkButton.Name = "loadNetworkButton";
			this.loadNetworkButton.Size = new System.Drawing.Size(160, 23);
			this.loadNetworkButton.TabIndex = 0;
			this.loadNetworkButton.Text = "Load neural network from file";
			this.loadNetworkButton.UseVisualStyleBackColor = true;
			this.loadNetworkButton.Click += new System.EventHandler(this.LoadNetworkButtonCLick);
			// 
			// saveNetworkButton
			// 
			this.saveNetworkButton.Location = new System.Drawing.Point(4, 62);
			this.saveNetworkButton.Name = "saveNetworkButton";
			this.saveNetworkButton.Size = new System.Drawing.Size(160, 23);
			this.saveNetworkButton.TabIndex = 2;
			this.saveNetworkButton.Text = "Save neural network to file";
			this.saveNetworkButton.UseVisualStyleBackColor = true;
			this.saveNetworkButton.Visible = false;
			this.saveNetworkButton.Click += new System.EventHandler(this.SaveNetworkButtonCLick);
			// 
			// createNetworkButton
			// 
			this.createNetworkButton.Location = new System.Drawing.Point(4, 33);
			this.createNetworkButton.Name = "createNetworkButton";
			this.createNetworkButton.Size = new System.Drawing.Size(160, 23);
			this.createNetworkButton.TabIndex = 1;
			this.createNetworkButton.Text = "Create new neural network";
			this.createNetworkButton.UseVisualStyleBackColor = true;
			this.createNetworkButton.Click += new System.EventHandler(this.CreateNetworkButtonCLick);
			// 
			// networkFormatTextBox
			// 
			this.networkFormatTextBox.Location = new System.Drawing.Point(170, 4);
			this.networkFormatTextBox.Multiline = true;
			this.networkFormatTextBox.Name = "networkFormatTextBox";
			this.networkFormatTextBox.Size = new System.Drawing.Size(227, 110);
			this.networkFormatTextBox.TabIndex = 4;
			// 
			// networkOpenFileDialog
			// 
			this.networkOpenFileDialog.DefaultExt = "per";
			this.networkOpenFileDialog.Filter = "perceptron files|*.per";
			// 
			// networkSaveFileDialog
			// 
			this.networkSaveFileDialog.DefaultExt = "per";
			this.networkSaveFileDialog.Filter = "perceptron files|*.per";
			// 
			// clearButton
			// 
			this.clearButton.Location = new System.Drawing.Point(4, 91);
			this.clearButton.Name = "clearButton";
			this.clearButton.Size = new System.Drawing.Size(75, 23);
			this.clearButton.TabIndex = 3;
			this.clearButton.Text = "Clear";
			this.clearButton.UseVisualStyleBackColor = true;
			this.clearButton.Visible = false;
			this.clearButton.Click += new System.EventHandler(this.ClearButtonClick);
			// 
			// NeuralNetworkControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.clearButton);
			this.Controls.Add(this.networkFormatTextBox);
			this.Controls.Add(this.createNetworkButton);
			this.Controls.Add(this.saveNetworkButton);
			this.Controls.Add(this.loadNetworkButton);
			this.Name = "NeuralNetworkControl";
			this.Size = new System.Drawing.Size(400, 120);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button loadNetworkButton;
		private System.Windows.Forms.Button saveNetworkButton;
		private System.Windows.Forms.Button createNetworkButton;
		private System.Windows.Forms.TextBox networkFormatTextBox;
		private System.Windows.Forms.OpenFileDialog networkOpenFileDialog;
		private System.Windows.Forms.SaveFileDialog networkSaveFileDialog;
		private System.Windows.Forms.Button clearButton;
	}
}
