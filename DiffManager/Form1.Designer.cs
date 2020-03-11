namespace DiffManager
{
    partial class Form1
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
            this.File = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.Format = new System.Windows.Forms.TextBox();
            this.StatusBar = new System.Windows.Forms.ProgressBar();
            this.Start = new System.Windows.Forms.Button();
            this.Frame = new System.Windows.Forms.NumericUpDown();
            this.EncoderType = new System.Windows.Forms.ComboBox();
            this.Status = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.Path = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.Ratio = new System.Windows.Forms.NumericUpDown();
            this.lable5 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.Frame)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Ratio)).BeginInit();
            this.SuspendLayout();
            // 
            // File
            // 
            this.File.Location = new System.Drawing.Point(47, 39);
            this.File.Name = "File";
            this.File.Size = new System.Drawing.Size(100, 20);
            this.File.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 42);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Name";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(182, 42);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(36, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Frame";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(2, 70);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(39, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Format";
            // 
            // Format
            // 
            this.Format.Location = new System.Drawing.Point(47, 67);
            this.Format.Name = "Format";
            this.Format.Size = new System.Drawing.Size(100, 20);
            this.Format.TabIndex = 5;
            this.Format.Text = "{0}_{1:D3}.png";
            // 
            // StatusBar
            // 
            this.StatusBar.Location = new System.Drawing.Point(5, 95);
            this.StatusBar.Name = "StatusBar";
            this.StatusBar.Size = new System.Drawing.Size(282, 23);
            this.StatusBar.TabIndex = 6;
            // 
            // Start
            // 
            this.Start.Location = new System.Drawing.Point(212, 124);
            this.Start.Name = "Start";
            this.Start.Size = new System.Drawing.Size(75, 23);
            this.Start.TabIndex = 7;
            this.Start.Text = "Start";
            this.Start.UseVisualStyleBackColor = true;
            this.Start.Click += new System.EventHandler(this.Start_Click);
            // 
            // Frame
            // 
            this.Frame.Location = new System.Drawing.Point(229, 39);
            this.Frame.Maximum = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.Frame.Name = "Frame";
            this.Frame.Size = new System.Drawing.Size(58, 20);
            this.Frame.TabIndex = 8;
            // 
            // EncoderType
            // 
            this.EncoderType.FormattingEnabled = true;
            this.EncoderType.Items.AddRange(new object[] {
            "CompressionLZW",
            "CompressionCCITT3",
            "CompressionCCITT4",
            "CompressionRle",
            "CompressionNone"});
            this.EncoderType.Location = new System.Drawing.Point(163, 66);
            this.EncoderType.Name = "EncoderType";
            this.EncoderType.Size = new System.Drawing.Size(124, 21);
            this.EncoderType.TabIndex = 9;
            this.EncoderType.Text = "CompressionLZW";
            // 
            // Status
            // 
            this.Status.AutoSize = true;
            this.Status.Location = new System.Drawing.Point(12, 105);
            this.Status.Name = "Status";
            this.Status.Size = new System.Drawing.Size(0, 13);
            this.Status.TabIndex = 10;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 15);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Path";
            // 
            // Path
            // 
            this.Path.Location = new System.Drawing.Point(47, 12);
            this.Path.Name = "Path";
            this.Path.Size = new System.Drawing.Size(205, 20);
            this.Path.TabIndex = 12;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(267, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(20, 20);
            this.button1.TabIndex = 13;
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Ratio
            // 
            this.Ratio.DecimalPlaces = 2;
            this.Ratio.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.Ratio.Location = new System.Drawing.Point(47, 126);
            this.Ratio.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.Ratio.Name = "Ratio";
            this.Ratio.Size = new System.Drawing.Size(45, 20);
            this.Ratio.TabIndex = 14;
            this.Ratio.ThousandsSeparator = true;
            this.Ratio.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // lable5
            // 
            this.lable5.AutoSize = true;
            this.lable5.Location = new System.Drawing.Point(12, 129);
            this.lable5.Name = "lable5";
            this.lable5.Size = new System.Drawing.Size(32, 13);
            this.lable5.TabIndex = 15;
            this.lable5.Text = "Ratio";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(295, 156);
            this.Controls.Add(this.lable5);
            this.Controls.Add(this.Ratio);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.Path);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.Status);
            this.Controls.Add(this.EncoderType);
            this.Controls.Add(this.Frame);
            this.Controls.Add(this.Start);
            this.Controls.Add(this.StatusBar);
            this.Controls.Add(this.Format);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.File);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.Frame)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Ratio)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox File;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox Format;
        private System.Windows.Forms.ProgressBar StatusBar;
        private System.Windows.Forms.Button Start;
        private System.Windows.Forms.NumericUpDown Frame;
        private System.Windows.Forms.ComboBox EncoderType;
        private System.Windows.Forms.Label Status;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox Path;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.NumericUpDown Ratio;
        private System.Windows.Forms.Label lable5;
    }
}

