namespace GUI
{
	partial class GUIForm
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

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.networkErrorLabel = new System.Windows.Forms.Label();
			this.iterationLabel = new System.Windows.Forms.Label();
			this.startingIndexLabel = new System.Windows.Forms.Label();
			this.endingIndexLabel = new System.Windows.Forms.Label();
			this.learnRateLabel = new System.Windows.Forms.Label();
			this.endingIndexNumericUpDown = new System.Windows.Forms.NumericUpDown();
			this.startingIndexNumericUpDown = new System.Windows.Forms.NumericUpDown();
			this.learnRateUpDown = new System.Windows.Forms.NumericUpDown();
			this.trainButton = new System.Windows.Forms.Button();
			this.tabControl = new System.Windows.Forms.TabControl();
			this.trainTabPage = new System.Windows.Forms.TabPage();
			this.testingTabPage = new System.Windows.Forms.TabPage();
			this.percentageLabel = new System.Windows.Forms.Label();
			this.incorrectAmountLabel = new System.Windows.Forms.Label();
			this.correctAmountLabel = new System.Windows.Forms.Label();
			this.testStartingIndexNumericUpDown = new System.Windows.Forms.NumericUpDown();
			this.fileTestButton = new System.Windows.Forms.Button();
			this.testStartingIndexLabel = new System.Windows.Forms.Label();
			this.testEndingIndexLabel = new System.Windows.Forms.Label();
			this.testEndingIndexNumericUpDown = new System.Windows.Forms.NumericUpDown();
			this.singleTestTabPage = new System.Windows.Forms.TabPage();
			this.clearImageButton = new System.Windows.Forms.Button();
			this.digitDraw = new GUI.View.Controls.DigitDraw();
			this.singleTestResultLabel = new System.Windows.Forms.Label();
			this.singleTestButton = new System.Windows.Forms.Button();
			this.singleTestDescriptionLabel = new System.Windows.Forms.Label();
			this.digitSetControl = new GUI.View.Controls.DigitSetControl();
			this.neuralNetworkControl = new GUI.Controls.NeuralNetworkControl();
			((System.ComponentModel.ISupportInitialize)(this.endingIndexNumericUpDown)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.startingIndexNumericUpDown)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.learnRateUpDown)).BeginInit();
			this.tabControl.SuspendLayout();
			this.trainTabPage.SuspendLayout();
			this.testingTabPage.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.testStartingIndexNumericUpDown)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.testEndingIndexNumericUpDown)).BeginInit();
			this.singleTestTabPage.SuspendLayout();
			this.SuspendLayout();
			// 
			// networkErrorLabel
			// 
			this.networkErrorLabel.AutoSize = true;
			this.networkErrorLabel.Location = new System.Drawing.Point(180, 11);
			this.networkErrorLabel.Name = "networkErrorLabel";
			this.networkErrorLabel.Size = new System.Drawing.Size(0, 13);
			this.networkErrorLabel.TabIndex = 2;
			// 
			// iterationLabel
			// 
			this.iterationLabel.AutoSize = true;
			this.iterationLabel.Location = new System.Drawing.Point(180, 32);
			this.iterationLabel.Name = "iterationLabel";
			this.iterationLabel.Size = new System.Drawing.Size(0, 13);
			this.iterationLabel.TabIndex = 10;
			// 
			// startingIndexLabel
			// 
			this.startingIndexLabel.AutoSize = true;
			this.startingIndexLabel.Location = new System.Drawing.Point(7, 32);
			this.startingIndexLabel.Name = "startingIndexLabel";
			this.startingIndexLabel.Size = new System.Drawing.Size(71, 13);
			this.startingIndexLabel.TabIndex = 9;
			this.startingIndexLabel.Text = "Starting index";
			// 
			// endingIndexLabel
			// 
			this.endingIndexLabel.AutoSize = true;
			this.endingIndexLabel.Location = new System.Drawing.Point(7, 53);
			this.endingIndexLabel.Name = "endingIndexLabel";
			this.endingIndexLabel.Size = new System.Drawing.Size(68, 13);
			this.endingIndexLabel.TabIndex = 8;
			this.endingIndexLabel.Text = "Ending index";
			// 
			// learnRateLabel
			// 
			this.learnRateLabel.AutoSize = true;
			this.learnRateLabel.Location = new System.Drawing.Point(7, 11);
			this.learnRateLabel.Name = "learnRateLabel";
			this.learnRateLabel.Size = new System.Drawing.Size(55, 13);
			this.learnRateLabel.TabIndex = 7;
			this.learnRateLabel.Text = "Learn rate";
			// 
			// endingIndexNumericUpDown
			// 
			this.endingIndexNumericUpDown.Location = new System.Drawing.Point(94, 51);
			this.endingIndexNumericUpDown.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
			this.endingIndexNumericUpDown.Name = "endingIndexNumericUpDown";
			this.endingIndexNumericUpDown.Size = new System.Drawing.Size(80, 20);
			this.endingIndexNumericUpDown.TabIndex = 6;
			// 
			// startingIndexNumericUpDown
			// 
			this.startingIndexNumericUpDown.Location = new System.Drawing.Point(94, 30);
			this.startingIndexNumericUpDown.Maximum = new decimal(new int[] {
            10000000,
            0,
            0,
            0});
			this.startingIndexNumericUpDown.Name = "startingIndexNumericUpDown";
			this.startingIndexNumericUpDown.Size = new System.Drawing.Size(80, 20);
			this.startingIndexNumericUpDown.TabIndex = 5;
			// 
			// learnRateUpDown
			// 
			this.learnRateUpDown.DecimalPlaces = 2;
			this.learnRateUpDown.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
			this.learnRateUpDown.Location = new System.Drawing.Point(94, 9);
			this.learnRateUpDown.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
			this.learnRateUpDown.Name = "learnRateUpDown";
			this.learnRateUpDown.Size = new System.Drawing.Size(80, 20);
			this.learnRateUpDown.TabIndex = 4;
			// 
			// trainButton
			// 
			this.trainButton.Location = new System.Drawing.Point(10, 87);
			this.trainButton.Name = "trainButton";
			this.trainButton.Size = new System.Drawing.Size(75, 23);
			this.trainButton.TabIndex = 3;
			this.trainButton.Text = "Train";
			this.trainButton.UseVisualStyleBackColor = true;
			this.trainButton.Click += new System.EventHandler(this.TrainButtonClick);
			// 
			// tabControl
			// 
			this.tabControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.tabControl.Controls.Add(this.trainTabPage);
			this.tabControl.Controls.Add(this.testingTabPage);
			this.tabControl.Controls.Add(this.singleTestTabPage);
			this.tabControl.Location = new System.Drawing.Point(0, 241);
			this.tabControl.Name = "tabControl";
			this.tabControl.SelectedIndex = 0;
			this.tabControl.Size = new System.Drawing.Size(687, 322);
			this.tabControl.TabIndex = 4;
			// 
			// trainTabPage
			// 
			this.trainTabPage.Controls.Add(this.iterationLabel);
			this.trainTabPage.Controls.Add(this.startingIndexNumericUpDown);
			this.trainTabPage.Controls.Add(this.networkErrorLabel);
			this.trainTabPage.Controls.Add(this.trainButton);
			this.trainTabPage.Controls.Add(this.startingIndexLabel);
			this.trainTabPage.Controls.Add(this.learnRateUpDown);
			this.trainTabPage.Controls.Add(this.endingIndexLabel);
			this.trainTabPage.Controls.Add(this.endingIndexNumericUpDown);
			this.trainTabPage.Controls.Add(this.learnRateLabel);
			this.trainTabPage.Location = new System.Drawing.Point(4, 22);
			this.trainTabPage.Name = "trainTabPage";
			this.trainTabPage.Padding = new System.Windows.Forms.Padding(3);
			this.trainTabPage.Size = new System.Drawing.Size(679, 296);
			this.trainTabPage.TabIndex = 0;
			this.trainTabPage.Text = "Training";
			this.trainTabPage.UseVisualStyleBackColor = true;
			// 
			// testingTabPage
			// 
			this.testingTabPage.Controls.Add(this.percentageLabel);
			this.testingTabPage.Controls.Add(this.incorrectAmountLabel);
			this.testingTabPage.Controls.Add(this.correctAmountLabel);
			this.testingTabPage.Controls.Add(this.testStartingIndexNumericUpDown);
			this.testingTabPage.Controls.Add(this.fileTestButton);
			this.testingTabPage.Controls.Add(this.testStartingIndexLabel);
			this.testingTabPage.Controls.Add(this.testEndingIndexLabel);
			this.testingTabPage.Controls.Add(this.testEndingIndexNumericUpDown);
			this.testingTabPage.Location = new System.Drawing.Point(4, 22);
			this.testingTabPage.Name = "testingTabPage";
			this.testingTabPage.Padding = new System.Windows.Forms.Padding(3);
			this.testingTabPage.Size = new System.Drawing.Size(679, 296);
			this.testingTabPage.TabIndex = 1;
			this.testingTabPage.Text = "Test files";
			this.testingTabPage.UseVisualStyleBackColor = true;
			// 
			// percentageLabel
			// 
			this.percentageLabel.AutoSize = true;
			this.percentageLabel.Location = new System.Drawing.Point(182, 53);
			this.percentageLabel.Name = "percentageLabel";
			this.percentageLabel.Size = new System.Drawing.Size(0, 13);
			this.percentageLabel.TabIndex = 18;
			// 
			// incorrectAmountLabel
			// 
			this.incorrectAmountLabel.AutoSize = true;
			this.incorrectAmountLabel.Location = new System.Drawing.Point(182, 33);
			this.incorrectAmountLabel.Name = "incorrectAmountLabel";
			this.incorrectAmountLabel.Size = new System.Drawing.Size(0, 13);
			this.incorrectAmountLabel.TabIndex = 17;
			// 
			// correctAmountLabel
			// 
			this.correctAmountLabel.AutoSize = true;
			this.correctAmountLabel.Location = new System.Drawing.Point(182, 12);
			this.correctAmountLabel.Name = "correctAmountLabel";
			this.correctAmountLabel.Size = new System.Drawing.Size(0, 13);
			this.correctAmountLabel.TabIndex = 16;
			// 
			// testStartingIndexNumericUpDown
			// 
			this.testStartingIndexNumericUpDown.Location = new System.Drawing.Point(95, 10);
			this.testStartingIndexNumericUpDown.Maximum = new decimal(new int[] {
            10000000,
            0,
            0,
            0});
			this.testStartingIndexNumericUpDown.Name = "testStartingIndexNumericUpDown";
			this.testStartingIndexNumericUpDown.Size = new System.Drawing.Size(80, 20);
			this.testStartingIndexNumericUpDown.TabIndex = 11;
			// 
			// fileTestButton
			// 
			this.fileTestButton.Location = new System.Drawing.Point(11, 67);
			this.fileTestButton.Name = "fileTestButton";
			this.fileTestButton.Size = new System.Drawing.Size(75, 23);
			this.fileTestButton.TabIndex = 10;
			this.fileTestButton.Text = "Test";
			this.fileTestButton.UseVisualStyleBackColor = true;
			this.fileTestButton.Click += new System.EventHandler(this.TestButtonClick);
			// 
			// testStartingIndexLabel
			// 
			this.testStartingIndexLabel.AutoSize = true;
			this.testStartingIndexLabel.Location = new System.Drawing.Point(8, 12);
			this.testStartingIndexLabel.Name = "testStartingIndexLabel";
			this.testStartingIndexLabel.Size = new System.Drawing.Size(71, 13);
			this.testStartingIndexLabel.TabIndex = 14;
			this.testStartingIndexLabel.Text = "Starting index";
			// 
			// testEndingIndexLabel
			// 
			this.testEndingIndexLabel.AutoSize = true;
			this.testEndingIndexLabel.Location = new System.Drawing.Point(8, 33);
			this.testEndingIndexLabel.Name = "testEndingIndexLabel";
			this.testEndingIndexLabel.Size = new System.Drawing.Size(68, 13);
			this.testEndingIndexLabel.TabIndex = 13;
			this.testEndingIndexLabel.Text = "Ending index";
			// 
			// testEndingIndexNumericUpDown
			// 
			this.testEndingIndexNumericUpDown.Location = new System.Drawing.Point(95, 31);
			this.testEndingIndexNumericUpDown.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
			this.testEndingIndexNumericUpDown.Name = "testEndingIndexNumericUpDown";
			this.testEndingIndexNumericUpDown.Size = new System.Drawing.Size(80, 20);
			this.testEndingIndexNumericUpDown.TabIndex = 12;
			// 
			// singleTestTabPage
			// 
			this.singleTestTabPage.BackColor = System.Drawing.Color.DarkGray;
			this.singleTestTabPage.Controls.Add(this.clearImageButton);
			this.singleTestTabPage.Controls.Add(this.digitDraw);
			this.singleTestTabPage.Controls.Add(this.singleTestResultLabel);
			this.singleTestTabPage.Controls.Add(this.singleTestButton);
			this.singleTestTabPage.Controls.Add(this.singleTestDescriptionLabel);
			this.singleTestTabPage.Location = new System.Drawing.Point(4, 22);
			this.singleTestTabPage.Name = "singleTestTabPage";
			this.singleTestTabPage.Padding = new System.Windows.Forms.Padding(3);
			this.singleTestTabPage.Size = new System.Drawing.Size(679, 296);
			this.singleTestTabPage.TabIndex = 2;
			this.singleTestTabPage.Text = "Single test";
			// 
			// clearImageButton
			// 
			this.clearImageButton.Location = new System.Drawing.Point(312, 127);
			this.clearImageButton.Name = "clearImageButton";
			this.clearImageButton.Size = new System.Drawing.Size(75, 23);
			this.clearImageButton.TabIndex = 5;
			this.clearImageButton.Text = "Clear";
			this.clearImageButton.UseVisualStyleBackColor = true;
			this.clearImageButton.Click += new System.EventHandler(this.ClearImageButtonClick);
			// 
			// digitDraw
			// 
			this.digitDraw.Location = new System.Drawing.Point(8, 6);
			this.digitDraw.Name = "digitDraw";
			this.digitDraw.Size = new System.Drawing.Size(280, 280);
			this.digitDraw.TabIndex = 4;
			// 
			// singleTestResultLabel
			// 
			this.singleTestResultLabel.AutoSize = true;
			this.singleTestResultLabel.Location = new System.Drawing.Point(309, 74);
			this.singleTestResultLabel.Name = "singleTestResultLabel";
			this.singleTestResultLabel.Size = new System.Drawing.Size(0, 13);
			this.singleTestResultLabel.TabIndex = 3;
			// 
			// singleTestButton
			// 
			this.singleTestButton.Location = new System.Drawing.Point(312, 37);
			this.singleTestButton.Name = "singleTestButton";
			this.singleTestButton.Size = new System.Drawing.Size(75, 23);
			this.singleTestButton.TabIndex = 2;
			this.singleTestButton.Text = "Test";
			this.singleTestButton.UseVisualStyleBackColor = true;
			this.singleTestButton.Click += new System.EventHandler(this.TestSingleButtonClick);
			// 
			// singleTestDescriptionLabel
			// 
			this.singleTestDescriptionLabel.AutoSize = true;
			this.singleTestDescriptionLabel.Location = new System.Drawing.Point(309, 7);
			this.singleTestDescriptionLabel.Name = "singleTestDescriptionLabel";
			this.singleTestDescriptionLabel.Size = new System.Drawing.Size(86, 13);
			this.singleTestDescriptionLabel.TabIndex = 1;
			this.singleTestDescriptionLabel.Text = "Draw digit to test";
			// 
			// digitSetControl
			// 
			this.digitSetControl.AutoSize = true;
			this.digitSetControl.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.digitSetControl.Location = new System.Drawing.Point(15, 138);
			this.digitSetControl.Name = "digitSetControl";
			this.digitSetControl.Size = new System.Drawing.Size(114, 88);
			this.digitSetControl.TabIndex = 1;
			// 
			// neuralNetworkControl
			// 
			this.neuralNetworkControl.Location = new System.Drawing.Point(12, 12);
			this.neuralNetworkControl.Name = "neuralNetworkControl";
			this.neuralNetworkControl.Size = new System.Drawing.Size(400, 120);
			this.neuralNetworkControl.TabIndex = 0;
			// 
			// GUIForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.ClientSize = new System.Drawing.Size(684, 562);
			this.Controls.Add(this.tabControl);
			this.Controls.Add(this.digitSetControl);
			this.Controls.Add(this.neuralNetworkControl);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "GUIForm";
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
			this.Text = "Perceptron GUI";
			((System.ComponentModel.ISupportInitialize)(this.endingIndexNumericUpDown)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.startingIndexNumericUpDown)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.learnRateUpDown)).EndInit();
			this.tabControl.ResumeLayout(false);
			this.trainTabPage.ResumeLayout(false);
			this.trainTabPage.PerformLayout();
			this.testingTabPage.ResumeLayout(false);
			this.testingTabPage.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.testStartingIndexNumericUpDown)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.testEndingIndexNumericUpDown)).EndInit();
			this.singleTestTabPage.ResumeLayout(false);
			this.singleTestTabPage.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private Controls.NeuralNetworkControl neuralNetworkControl;
		private View.Controls.DigitSetControl digitSetControl;
		public System.Windows.Forms.Label networkErrorLabel;
		private System.Windows.Forms.Button trainButton;
		public System.Windows.Forms.Label iterationLabel;
		private System.Windows.Forms.Label startingIndexLabel;
		private System.Windows.Forms.Label endingIndexLabel;
		private System.Windows.Forms.Label learnRateLabel;
		private System.Windows.Forms.NumericUpDown endingIndexNumericUpDown;
		private System.Windows.Forms.NumericUpDown startingIndexNumericUpDown;
		private System.Windows.Forms.NumericUpDown learnRateUpDown;
		private System.Windows.Forms.TabControl tabControl;
		private System.Windows.Forms.TabPage trainTabPage;
		private System.Windows.Forms.TabPage testingTabPage;
		private System.Windows.Forms.Label percentageLabel;
		private System.Windows.Forms.Label incorrectAmountLabel;
		private System.Windows.Forms.Label correctAmountLabel;
		private System.Windows.Forms.NumericUpDown testStartingIndexNumericUpDown;
		private System.Windows.Forms.Button fileTestButton;
		private System.Windows.Forms.Label testStartingIndexLabel;
		private System.Windows.Forms.Label testEndingIndexLabel;
		private System.Windows.Forms.NumericUpDown testEndingIndexNumericUpDown;
		private System.Windows.Forms.TabPage singleTestTabPage;
		private System.Windows.Forms.Label singleTestResultLabel;
		private System.Windows.Forms.Button singleTestButton;
		private System.Windows.Forms.Label singleTestDescriptionLabel;
		private View.Controls.DigitDraw digitDraw;
		private System.Windows.Forms.Button clearImageButton;
	}
}

