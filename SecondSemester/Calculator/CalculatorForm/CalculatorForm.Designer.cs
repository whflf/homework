namespace CalculatorUI
{
    partial class CalculatorForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            mainPanel = new TableLayoutPanel();
            inputTextBox = new TextBox();
            buttonPanel = new TableLayoutPanel();
            button1 = new Button();
            button2 = new Button();
            button3 = new Button();
            buttonPlus = new Button();
            button4 = new Button();
            button5 = new Button();
            button6 = new Button();
            buttonMinus = new Button();
            button7 = new Button();
            button8 = new Button();
            button9 = new Button();
            buttonTimes = new Button();
            buttonClear = new Button();
            button0 = new Button();
            buttonEqual = new Button();
            buttonSlash = new Button();
            mainPanel.SuspendLayout();
            buttonPanel.SuspendLayout();
            SuspendLayout();
            // 
            // mainPanel
            // 
            mainPanel.ColumnCount = 1;
            mainPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            mainPanel.Controls.Add(inputTextBox, 0, 0);
            mainPanel.Controls.Add(buttonPanel, 0, 1);
            mainPanel.Dock = DockStyle.Fill;
            mainPanel.Location = new Point(0, 0);
            mainPanel.Name = "mainPanel";
            mainPanel.RowCount = 2;
            mainPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 23.37164F));
            mainPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 76.62836F));
            mainPanel.Size = new Size(387, 504);
            mainPanel.TabIndex = 0;
            // 
            // inputTextBox
            // 
            inputTextBox.BackColor = Color.FromArgb(255, 217, 238);
            inputTextBox.BorderStyle = BorderStyle.None;
            inputTextBox.Dock = DockStyle.Fill;
            inputTextBox.Font = new Font("Arial Rounded MT Bold", 59F, FontStyle.Regular, GraphicsUnit.Point, 0);
            inputTextBox.ForeColor = Color.FromArgb(111, 81, 173);
            inputTextBox.Location = new Point(3, 3);
            inputTextBox.Name = "inputTextBox";
            inputTextBox.ReadOnly = true;
            inputTextBox.Size = new Size(381, 114);
            inputTextBox.TabIndex = 0;
            inputTextBox.TabStop = false;
            inputTextBox.Text = "0";
            inputTextBox.TextAlign = HorizontalAlignment.Right;
            // 
            // buttonPanel
            // 
            buttonPanel.BackColor = Color.FromArgb(255, 217, 238);
            buttonPanel.ColumnCount = 4;
            buttonPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 25F));
            buttonPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 25F));
            buttonPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 25F));
            buttonPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 25F));
            buttonPanel.Controls.Add(button1, 0, 0);
            buttonPanel.Controls.Add(button2, 1, 0);
            buttonPanel.Controls.Add(button3, 2, 0);
            buttonPanel.Controls.Add(buttonPlus, 3, 0);
            buttonPanel.Controls.Add(button4, 0, 1);
            buttonPanel.Controls.Add(button5, 1, 1);
            buttonPanel.Controls.Add(button6, 2, 1);
            buttonPanel.Controls.Add(buttonMinus, 3, 1);
            buttonPanel.Controls.Add(button7, 0, 2);
            buttonPanel.Controls.Add(button8, 1, 2);
            buttonPanel.Controls.Add(button9, 2, 2);
            buttonPanel.Controls.Add(buttonTimes, 3, 2);
            buttonPanel.Controls.Add(buttonClear, 0, 3);
            buttonPanel.Controls.Add(button0, 1, 3);
            buttonPanel.Controls.Add(buttonEqual, 2, 3);
            buttonPanel.Controls.Add(buttonSlash, 3, 3);
            buttonPanel.Dock = DockStyle.Fill;
            buttonPanel.Location = new Point(3, 120);
            buttonPanel.Name = "buttonPanel";
            buttonPanel.RowCount = 4;
            buttonPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 25F));
            buttonPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 25F));
            buttonPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 25F));
            buttonPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 25F));
            buttonPanel.Size = new Size(381, 381);
            buttonPanel.TabIndex = 1;
            // 
            // button1
            // 
            button1.BackColor = Color.FromArgb(190, 157, 223);
            button1.Dock = DockStyle.Fill;
            button1.FlatAppearance.BorderColor = Color.FromArgb(149, 121, 209);
            button1.FlatAppearance.BorderSize = 5;
            button1.FlatStyle = FlatStyle.Flat;
            button1.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            button1.ForeColor = Color.FromArgb(149, 121, 209);
            button1.Location = new Point(3, 3);
            button1.Name = "button1";
            button1.Size = new Size(89, 89);
            button1.TabIndex = 0;
            button1.Text = "1";
            button1.UseVisualStyleBackColor = false;
            button1.Click += ButtonDigit_Click;
            // 
            // button2
            // 
            button2.BackColor = Color.FromArgb(190, 157, 223);
            button2.Dock = DockStyle.Fill;
            button2.FlatAppearance.BorderColor = Color.FromArgb(149, 121, 209);
            button2.FlatAppearance.BorderSize = 5;
            button2.FlatStyle = FlatStyle.Flat;
            button2.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            button2.ForeColor = Color.FromArgb(149, 121, 209);
            button2.Location = new Point(98, 3);
            button2.Name = "button2";
            button2.Size = new Size(89, 89);
            button2.TabIndex = 1;
            button2.Text = "2";
            button2.UseVisualStyleBackColor = true;
            button2.Click += ButtonDigit_Click;
            // 
            // button3
            // 
            button3.BackColor = Color.FromArgb(190, 157, 223);
            button3.Dock = DockStyle.Fill;
            button3.FlatAppearance.BorderColor = Color.FromArgb(149, 121, 209);
            button3.FlatAppearance.BorderSize = 5;
            button3.FlatStyle = FlatStyle.Flat;
            button3.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            button3.ForeColor = Color.FromArgb(149, 121, 209);
            button3.Location = new Point(193, 3);
            button3.Name = "button3";
            button3.Size = new Size(89, 89);
            button3.TabIndex = 2;
            button3.Text = "3";
            button3.UseVisualStyleBackColor = true;
            button3.Click += ButtonDigit_Click;
            // 
            // buttonPlus
            // 
            buttonPlus.BackColor = Color.FromArgb(149, 121, 209);
            buttonPlus.Dock = DockStyle.Fill;
            buttonPlus.FlatAppearance.BorderColor = Color.FromArgb(111, 81, 173);
            buttonPlus.FlatAppearance.BorderSize = 5;
            buttonPlus.FlatStyle = FlatStyle.Flat;
            buttonPlus.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonPlus.ForeColor = Color.FromArgb(111, 81, 173);
            buttonPlus.Location = new Point(288, 3);
            buttonPlus.Name = "buttonPlus";
            buttonPlus.Size = new Size(90, 89);
            buttonPlus.TabIndex = 3;
            buttonPlus.Text = "+";
            buttonPlus.UseVisualStyleBackColor = true;
            buttonPlus.Click += ButtonOperator_Click;
            // 
            // button4
            // 
            button4.BackColor = Color.FromArgb(190, 157, 223);
            button4.Dock = DockStyle.Fill;
            button4.FlatAppearance.BorderColor = Color.FromArgb(149, 121, 209);
            button4.FlatAppearance.BorderSize = 5;
            button4.FlatStyle = FlatStyle.Flat;
            button4.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            button4.ForeColor = Color.FromArgb(149, 121, 209);
            button4.Location = new Point(3, 98);
            button4.Name = "button4";
            button4.Size = new Size(89, 89);
            button4.TabIndex = 4;
            button4.Text = "4";
            button4.UseVisualStyleBackColor = true;
            button4.Click += ButtonDigit_Click;
            // 
            // button5
            // 
            button5.BackColor = Color.FromArgb(190, 157, 223);
            button5.Dock = DockStyle.Fill;
            button5.FlatAppearance.BorderColor = Color.FromArgb(149, 121, 209);
            button5.FlatAppearance.BorderSize = 5;
            button5.FlatStyle = FlatStyle.Flat;
            button5.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            button5.ForeColor = Color.FromArgb(149, 121, 209);
            button5.Location = new Point(98, 98);
            button5.Name = "button5";
            button5.Size = new Size(89, 89);
            button5.TabIndex = 5;
            button5.Text = "5";
            button5.UseVisualStyleBackColor = true;
            button5.Click += ButtonDigit_Click;
            // 
            // button6
            // 
            button6.BackColor = Color.FromArgb(190, 157, 223);
            button6.Dock = DockStyle.Fill;
            button6.FlatAppearance.BorderColor = Color.FromArgb(149, 121, 209);
            button6.FlatAppearance.BorderSize = 5;
            button6.FlatStyle = FlatStyle.Flat;
            button6.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            button6.ForeColor = Color.FromArgb(149, 121, 209);
            button6.Location = new Point(193, 98);
            button6.Name = "button6";
            button6.Size = new Size(89, 89);
            button6.TabIndex = 6;
            button6.Text = "6";
            button6.UseVisualStyleBackColor = true;
            button6.Click += ButtonDigit_Click;
            // 
            // buttonMinus
            // 
            buttonMinus.BackColor = Color.FromArgb(149, 121, 209);
            buttonMinus.Dock = DockStyle.Fill;
            buttonMinus.FlatAppearance.BorderColor = Color.FromArgb(111, 81, 173);
            buttonMinus.FlatAppearance.BorderSize = 5;
            buttonMinus.FlatStyle = FlatStyle.Flat;
            buttonMinus.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonMinus.ForeColor = Color.FromArgb(111, 81, 173);
            buttonMinus.Location = new Point(288, 98);
            buttonMinus.Name = "buttonMinus";
            buttonMinus.Size = new Size(90, 89);
            buttonMinus.TabIndex = 7;
            buttonMinus.Text = "-";
            buttonMinus.UseVisualStyleBackColor = true;
            buttonMinus.Click += ButtonOperator_Click;
            // 
            // button7
            // 
            button7.BackColor = Color.FromArgb(190, 157, 223);
            button7.Dock = DockStyle.Fill;
            button7.FlatAppearance.BorderColor = Color.FromArgb(149, 121, 209);
            button7.FlatAppearance.BorderSize = 5;
            button7.FlatStyle = FlatStyle.Flat;
            button7.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            button7.ForeColor = Color.FromArgb(149, 121, 209);
            button7.Location = new Point(3, 193);
            button7.Name = "button7";
            button7.Size = new Size(89, 89);
            button7.TabIndex = 8;
            button7.Text = "7";
            button7.UseVisualStyleBackColor = true;
            button7.Click += ButtonDigit_Click;
            // 
            // button8
            // 
            button8.BackColor = Color.FromArgb(190, 157, 223);
            button8.Dock = DockStyle.Fill;
            button8.FlatAppearance.BorderColor = Color.FromArgb(149, 121, 209);
            button8.FlatAppearance.BorderSize = 5;
            button8.FlatStyle = FlatStyle.Flat;
            button8.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            button8.ForeColor = Color.FromArgb(149, 121, 209);
            button8.Location = new Point(98, 193);
            button8.Name = "button8";
            button8.Size = new Size(89, 89);
            button8.TabIndex = 9;
            button8.Text = "8";
            button8.UseVisualStyleBackColor = true;
            button8.Click += ButtonDigit_Click;
            // 
            // button9
            // 
            button9.BackColor = Color.FromArgb(190, 157, 223);
            button9.Dock = DockStyle.Fill;
            button9.FlatAppearance.BorderColor = Color.FromArgb(149, 121, 209);
            button9.FlatAppearance.BorderSize = 5;
            button9.FlatStyle = FlatStyle.Flat;
            button9.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            button9.ForeColor = Color.FromArgb(149, 121, 209);
            button9.Location = new Point(193, 193);
            button9.Name = "button9";
            button9.Size = new Size(89, 89);
            button9.TabIndex = 10;
            button9.Text = "9";
            button9.UseVisualStyleBackColor = true;
            button9.Click += ButtonDigit_Click;
            // 
            // buttonTimes
            // 
            buttonTimes.BackColor = Color.FromArgb(149, 121, 209);
            buttonTimes.Dock = DockStyle.Fill;
            buttonTimes.FlatAppearance.BorderColor = Color.FromArgb(111, 81, 173);
            buttonTimes.FlatAppearance.BorderSize = 5;
            buttonTimes.FlatStyle = FlatStyle.Flat;
            buttonTimes.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonTimes.ForeColor = Color.FromArgb(111, 81, 173);
            buttonTimes.Location = new Point(288, 193);
            buttonTimes.Name = "buttonTimes";
            buttonTimes.Size = new Size(90, 89);
            buttonTimes.TabIndex = 11;
            buttonTimes.Text = "×";
            buttonTimes.UseVisualStyleBackColor = true;
            buttonTimes.Click += ButtonOperator_Click;
            // 
            // buttonClear
            // 
            buttonClear.BackColor = Color.FromArgb(146, 221, 234);
            buttonClear.Dock = DockStyle.Fill;
            buttonClear.FlatAppearance.BorderColor = Color.FromArgb(88, 147, 184);
            buttonClear.FlatAppearance.BorderSize = 5;
            buttonClear.FlatStyle = FlatStyle.Flat;
            buttonClear.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonClear.ForeColor = Color.FromArgb(88, 147, 184);
            buttonClear.Location = new Point(3, 288);
            buttonClear.Name = "buttonClear";
            buttonClear.Size = new Size(89, 90);
            buttonClear.TabIndex = 12;
            buttonClear.Text = "C";
            buttonClear.UseVisualStyleBackColor = false;
            buttonClear.Click += ButtonClear_Click;
            // 
            // button0
            // 
            button0.BackColor = Color.FromArgb(190, 157, 223);
            button0.Dock = DockStyle.Fill;
            button0.FlatAppearance.BorderColor = Color.FromArgb(149, 121, 209);
            button0.FlatAppearance.BorderSize = 5;
            button0.FlatStyle = FlatStyle.Flat;
            button0.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            button0.ForeColor = Color.FromArgb(149, 121, 209);
            button0.Location = new Point(98, 288);
            button0.Name = "button0";
            button0.Size = new Size(89, 90);
            button0.TabIndex = 13;
            button0.Text = "0";
            button0.UseVisualStyleBackColor = true;
            button0.Click += ButtonDigit_Click;
            // 
            // buttonEqual
            // 
            buttonEqual.BackColor = Color.FromArgb(146, 221, 234);
            buttonEqual.Dock = DockStyle.Fill;
            buttonEqual.FlatAppearance.BorderColor = Color.FromArgb(88, 147, 184);
            buttonEqual.FlatAppearance.BorderSize = 5;
            buttonEqual.FlatStyle = FlatStyle.Flat;
            buttonEqual.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonEqual.ForeColor = Color.FromArgb(88, 147, 184);
            buttonEqual.Location = new Point(193, 288);
            buttonEqual.Name = "buttonEqual";
            buttonEqual.Size = new Size(89, 90);
            buttonEqual.TabIndex = 14;
            buttonEqual.Text = "=";
            buttonEqual.UseVisualStyleBackColor = false;
            buttonEqual.Click += ButtonEqual_Click;
            // 
            // buttonSlash
            // 
            buttonSlash.BackColor = Color.FromArgb(149, 121, 209);
            buttonSlash.Dock = DockStyle.Fill;
            buttonSlash.FlatAppearance.BorderColor = Color.FromArgb(111, 81, 173);
            buttonSlash.FlatAppearance.BorderSize = 5;
            buttonSlash.FlatStyle = FlatStyle.Flat;
            buttonSlash.Font = new Font("Arial Rounded MT Bold", 22F, FontStyle.Regular, GraphicsUnit.Point, 0);
            buttonSlash.ForeColor = Color.FromArgb(111, 81, 173);
            buttonSlash.Location = new Point(288, 288);
            buttonSlash.Name = "buttonSlash";
            buttonSlash.Size = new Size(90, 90);
            buttonSlash.TabIndex = 15;
            buttonSlash.Text = "/";
            buttonSlash.UseVisualStyleBackColor = true;
            buttonSlash.Click += ButtonOperator_Click;
            // 
            // CalculatorForm
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.FromArgb(255, 217, 238);
            ClientSize = new Size(387, 504);
            Controls.Add(mainPanel);
            MinimumSize = new Size(405, 551);
            Name = "CalculatorForm";
            Text = "Calculator";
            mainPanel.ResumeLayout(false);
            mainPanel.PerformLayout();
            buttonPanel.ResumeLayout(false);
            ResumeLayout(false);
        }

        #endregion

        private TableLayoutPanel mainPanel;
        private TextBox inputTextBox;
        private TableLayoutPanel buttonPanel;
        private Button button1;
        private Button button2;
        private Button button3;
        private Button buttonPlus;
        private Button button4;
        private Button button5;
        private Button button6;
        private Button buttonMinus;
        private Button button7;
        private Button button8;
        private Button button9;
        private Button buttonTimes;
        private Button buttonClear;
        private Button button0;
        private Button buttonEqual;
        private Button buttonSlash;
    }
}
