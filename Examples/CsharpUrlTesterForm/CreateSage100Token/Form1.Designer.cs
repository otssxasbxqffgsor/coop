namespace CreateSage100Token
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
            this.label1 = new System.Windows.Forms.Label();
            this.txtSageCustomerId = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtCompanyCode = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.txtFEIN = new System.Windows.Forms.TextBox();
            this.txtBaseUrl = new System.Windows.Forms.TextBox();
            this.txtLaunchDDP = new System.Windows.Forms.Button();
            this.btnExit = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.txtEmployeeCount = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.rdoErp100 = new System.Windows.Forms.RadioButton();
            this.rdoErp300 = new System.Windows.Forms.RadioButton();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.txtCompanyName = new System.Windows.Forms.TextBox();
            this.txtCompanyAddress1 = new System.Windows.Forms.TextBox();
            this.txtCompanyAddress2 = new System.Windows.Forms.TextBox();
            this.txtCompanyCity = new System.Windows.Forms.TextBox();
            this.cboCompanyState = new System.Windows.Forms.ComboBox();
            this.txtCompanyZip = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 43);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(96, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Sage Customer ID:";
            // 
            // txtSageCustomerId
            // 
            this.txtSageCustomerId.Location = new System.Drawing.Point(124, 40);
            this.txtSageCustomerId.Name = "txtSageCustomerId";
            this.txtSageCustomerId.Size = new System.Drawing.Size(229, 20);
            this.txtSageCustomerId.TabIndex = 4;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 74);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(82, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Company Code:";
            // 
            // txtCompanyCode
            // 
            this.txtCompanyCode.Location = new System.Drawing.Point(124, 70);
            this.txtCompanyCode.Name = "txtCompanyCode";
            this.txtCompanyCode.Size = new System.Drawing.Size(229, 20);
            this.txtCompanyCode.TabIndex = 6;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 103);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(34, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "FEIN:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 133);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(67, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "DDP Server:";
            // 
            // txtFEIN
            // 
            this.txtFEIN.Location = new System.Drawing.Point(124, 100);
            this.txtFEIN.Name = "txtFEIN";
            this.txtFEIN.Size = new System.Drawing.Size(229, 20);
            this.txtFEIN.TabIndex = 8;
            // 
            // txtBaseUrl
            // 
            this.txtBaseUrl.Location = new System.Drawing.Point(124, 130);
            this.txtBaseUrl.Name = "txtBaseUrl";
            this.txtBaseUrl.Size = new System.Drawing.Size(229, 20);
            this.txtBaseUrl.TabIndex = 10;
            // 
            // txtLaunchDDP
            // 
            this.txtLaunchDDP.Location = new System.Drawing.Point(278, 375);
            this.txtLaunchDDP.Name = "txtLaunchDDP";
            this.txtLaunchDDP.Size = new System.Drawing.Size(75, 23);
            this.txtLaunchDDP.TabIndex = 25;
            this.txtLaunchDDP.Text = "Open Form";
            this.txtLaunchDDP.UseVisualStyleBackColor = true;
            this.txtLaunchDDP.Click += new System.EventHandler(this.txtLaunchDDP_Click);
            // 
            // btnExit
            // 
            this.btnExit.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnExit.Location = new System.Drawing.Point(197, 375);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(75, 23);
            this.btnExit.TabIndex = 26;
            this.btnExit.Text = "Exit";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 163);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(87, 13);
            this.label5.TabIndex = 11;
            this.label5.Text = "Employee Count:";
            // 
            // txtEmployeeCount
            // 
            this.txtEmployeeCount.Location = new System.Drawing.Point(124, 160);
            this.txtEmployeeCount.Name = "txtEmployeeCount";
            this.txtEmployeeCount.Size = new System.Drawing.Size(229, 20);
            this.txtEmployeeCount.TabIndex = 12;
            this.txtEmployeeCount.Text = "50";
            this.txtEmployeeCount.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 13);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(32, 13);
            this.label6.TabIndex = 0;
            this.label6.Text = "ERP:";
            // 
            // rdoErp100
            // 
            this.rdoErp100.AutoSize = true;
            this.rdoErp100.Checked = true;
            this.rdoErp100.Location = new System.Drawing.Point(124, 13);
            this.rdoErp100.Name = "rdoErp100";
            this.rdoErp100.Size = new System.Drawing.Size(71, 17);
            this.rdoErp100.TabIndex = 1;
            this.rdoErp100.TabStop = true;
            this.rdoErp100.Text = "Sage 100";
            this.rdoErp100.UseVisualStyleBackColor = true;
            this.rdoErp100.CheckedChanged += new System.EventHandler(this.rdoErp100_CheckedChanged);
            // 
            // rdoErp300
            // 
            this.rdoErp300.AutoSize = true;
            this.rdoErp300.Location = new System.Drawing.Point(223, 13);
            this.rdoErp300.Name = "rdoErp300";
            this.rdoErp300.Size = new System.Drawing.Size(71, 17);
            this.rdoErp300.TabIndex = 2;
            this.rdoErp300.Text = "Sage 300";
            this.rdoErp300.UseVisualStyleBackColor = true;
            this.rdoErp300.CheckedChanged += new System.EventHandler(this.rdoErp300_CheckedChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(12, 193);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(85, 13);
            this.label7.TabIndex = 13;
            this.label7.Text = "Company Name:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(12, 223);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(80, 13);
            this.label8.TabIndex = 15;
            this.label8.Text = "Address Line 1:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(12, 253);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(80, 13);
            this.label9.TabIndex = 17;
            this.label9.Text = "Address Line 2:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(12, 283);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(27, 13);
            this.label10.TabIndex = 19;
            this.label10.Text = "City:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(12, 313);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(35, 13);
            this.label11.TabIndex = 21;
            this.label11.Text = "State:";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(12, 343);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(25, 13);
            this.label12.TabIndex = 23;
            this.label12.Text = "Zip:";
            // 
            // txtCompanyName
            // 
            this.txtCompanyName.Enabled = false;
            this.txtCompanyName.Location = new System.Drawing.Point(124, 190);
            this.txtCompanyName.Name = "txtCompanyName";
            this.txtCompanyName.Size = new System.Drawing.Size(229, 20);
            this.txtCompanyName.TabIndex = 14;
            // 
            // txtCompanyAddress1
            // 
            this.txtCompanyAddress1.Enabled = false;
            this.txtCompanyAddress1.Location = new System.Drawing.Point(124, 220);
            this.txtCompanyAddress1.Name = "txtCompanyAddress1";
            this.txtCompanyAddress1.Size = new System.Drawing.Size(229, 20);
            this.txtCompanyAddress1.TabIndex = 16;
            // 
            // txtCompanyAddress2
            // 
            this.txtCompanyAddress2.Enabled = false;
            this.txtCompanyAddress2.Location = new System.Drawing.Point(124, 250);
            this.txtCompanyAddress2.Name = "txtCompanyAddress2";
            this.txtCompanyAddress2.Size = new System.Drawing.Size(229, 20);
            this.txtCompanyAddress2.TabIndex = 18;
            // 
            // txtCompanyCity
            // 
            this.txtCompanyCity.Enabled = false;
            this.txtCompanyCity.Location = new System.Drawing.Point(124, 280);
            this.txtCompanyCity.Name = "txtCompanyCity";
            this.txtCompanyCity.Size = new System.Drawing.Size(229, 20);
            this.txtCompanyCity.TabIndex = 20;
            // 
            // cboCompanyState
            // 
            this.cboCompanyState.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboCompanyState.Enabled = false;
            this.cboCompanyState.FormattingEnabled = true;
            this.cboCompanyState.ItemHeight = 13;
            this.cboCompanyState.Location = new System.Drawing.Point(124, 310);
            this.cboCompanyState.Name = "cboCompanyState";
            this.cboCompanyState.Size = new System.Drawing.Size(229, 21);
            this.cboCompanyState.TabIndex = 22;
            // 
            // txtCompanyZip
            // 
            this.txtCompanyZip.Enabled = false;
            this.txtCompanyZip.Location = new System.Drawing.Point(124, 340);
            this.txtCompanyZip.Name = "txtCompanyZip";
            this.txtCompanyZip.Size = new System.Drawing.Size(229, 20);
            this.txtCompanyZip.TabIndex = 24;
            // 
            // Form1
            // 
            this.AcceptButton = this.txtLaunchDDP;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btnExit;
            this.ClientSize = new System.Drawing.Size(372, 415);
            this.Controls.Add(this.txtCompanyZip);
            this.Controls.Add(this.cboCompanyState);
            this.Controls.Add(this.txtCompanyCity);
            this.Controls.Add(this.txtCompanyAddress2);
            this.Controls.Add(this.txtCompanyAddress1);
            this.Controls.Add(this.txtCompanyName);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.rdoErp300);
            this.Controls.Add(this.rdoErp100);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.txtEmployeeCount);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.txtLaunchDDP);
            this.Controls.Add(this.txtBaseUrl);
            this.Controls.Add(this.txtFEIN);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtCompanyCode);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtSageCustomerId);
            this.Controls.Add(this.label1);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.ShowIcon = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "Create Sage 100 Login Token";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtSageCustomerId;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtCompanyCode;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtFEIN;
        private System.Windows.Forms.TextBox txtBaseUrl;
        private System.Windows.Forms.Button txtLaunchDDP;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtEmployeeCount;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.RadioButton rdoErp100;
        private System.Windows.Forms.RadioButton rdoErp300;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox txtCompanyName;
        private System.Windows.Forms.TextBox txtCompanyAddress1;
        private System.Windows.Forms.TextBox txtCompanyAddress2;
        private System.Windows.Forms.TextBox txtCompanyCity;
        private System.Windows.Forms.ComboBox cboCompanyState;
        private System.Windows.Forms.TextBox txtCompanyZip;
    }
}

