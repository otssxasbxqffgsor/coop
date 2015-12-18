using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Security.Cryptography;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace CreateSage100Token
{
    public partial class Form1 : Form
    {
        private const string URL_ENCRYPTION_CODE = "#e-rAwru7!?_acrum5g_sWeP6gEJU58\0";
//        private  Byte [] URL_ENCRYPTION_CODE = {
//    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
//};
        private const string URL_PATH_100 = "{0}Home/Sage100/?key={1}";
        private const string URL_PATH_300 = "{0}Home/Sage300/?key={1}";

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            txtBaseUrl.Text = ConfigurationManager.AppSettings["BaseUrl"];
            AddStates();
        }

        private void txtLaunchDDP_Click(object sender, EventArgs e)
        {
            if (txtBaseUrl.Text == string.Empty)
            {
                MessageBox.Show("You must supply a DDP Server URL", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            if (txtSageCustomerId.Text == string.Empty)
            {
                MessageBox.Show("You must supply a Sage Customer ID", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            if (txtCompanyCode.Text == string.Empty)
            {
                MessageBox.Show("You must supply a Sage 100 Company Code", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            int employeeCount;
            if (!int.TryParse(txtEmployeeCount.Text, out employeeCount))
            {
                MessageBox.Show("Employee Count must be numeric", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            try
            {
                string unencryptedString;
                if (rdoErp100.Checked)
                    unencryptedString = string.Format("businessPartnerId={0};sourceCompanyCode={1};sourceProduct=Sage100;fein={2};ts={3};ec={4};", txtSageCustomerId.Text, txtCompanyCode.Text, txtFEIN.Text, DateTime.Now.ToUniversalTime().ToString("yyyy'-'MM'-'dd'T'HH':'mm':'ss'.'fff'Z'"), employeeCount.ToString());
                else
                    unencryptedString = string.Format("businessPartnerId={0};sourceCompanyCode={1};sourceProduct=Sage300;fein={2};ts={3};ec={4};companyName={5};address1={6};address2={7};city={8};state={9};zip={10};", txtSageCustomerId.Text, txtCompanyCode.Text, txtFEIN.Text, DateTime.Now.ToUniversalTime().ToString("yyyy'-'MM'-'dd'T'HH':'mm':'ss'.'fff'Z'"), employeeCount.ToString(),
                        txtCompanyName.Text, txtCompanyAddress1.Text, txtCompanyAddress2.Text, txtCompanyCity.Text, ((State)cboCompanyState.SelectedItem).Abbreviation, txtCompanyZip.Text);

          //    unencryptedString = "businessPartnerId=2;sourceCompanyCode=2;sourceProduct=Sage100;fein=2;ts=2015-12-17T23:02:16.454Z;ec=50;";
              //  unencryptedString = "TestMe";
                byte[] unencryptedBytes = Encoding.ASCII.GetBytes(unencryptedString);
                byte[] cipherBytes = new byte[unencryptedBytes.Length];

                using (AesManaged aesAlg = new AesManaged())
                {
                    aesAlg.Mode = CipherMode.ECB;

                    aesAlg.BlockSize = 128;
                    aesAlg.KeySize = 256;
                    aesAlg.Padding = PaddingMode.PKCS7;
                    aesAlg.Key = Encoding.ASCII.GetBytes(URL_ENCRYPTION_CODE);
                    //aesAlg.Key = URL_ENCRYPTION_CODE;

                    ////// Create a encrytor to perform the stream transform.
                    ICryptoTransform encryptor = aesAlg.CreateEncryptor(aesAlg.Key, aesAlg.IV);
                    using (MemoryStream msEncrypt = new MemoryStream())
                    {
                        using (CryptoStream csEncrypt = new CryptoStream(msEncrypt, encryptor, CryptoStreamMode.Write))
                        {
                            using (StreamWriter swEncrypt = new StreamWriter(csEncrypt))
                            {

                                //Write all data to the stream.
                                swEncrypt.Write(unencryptedString);
                            }
                            cipherBytes = msEncrypt.ToArray();
                        }
                    }

                    //encryptor.TransformBlock(unencryptedBytes, 0, unencryptedBytes.Length, cipherBytes, 0);
                }

                string _encodedString = System.Web.HttpUtility.UrlEncode(Convert.ToBase64String(cipherBytes));
                string urlPath = (rdoErp100.Checked ? URL_PATH_100 : URL_PATH_300);
                string url = string.Format(urlPath, txtBaseUrl.Text + (txtBaseUrl.Text.EndsWith("/") ? "" : txtBaseUrl.Text + "/"), _encodedString);

               // String Encrypted by sage 100
                bool IsDeCryptWasTrue = Decrypt(Convert.ToBase64String(cipherBytes), unencryptedString);
               // String Ecncypted by sage 300
                bool IsCtWasTrue = Decrypt("sPIcTM8Lc21Kc/o+8Bqvwg==", unencryptedString);
         

               //jk/zTy1EYcVXLGATQXzPbw==
              // U2FsdGVkX1/tzkUAk7mJDQe5bXO6KaQdWyiAnUqJRR4=
                //"lc7HKBYbLWoM9N/bRJd4nQ=="
              //sPIcTM8Lc21Kc/o+8Bqvwg==
                Compaire(Convert.ToBase64String(cipherBytes), "");

                ProcessStartInfo si = new ProcessStartInfo(url);
                Process.Start(si);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error launching Prospect Form: " + ex.ToString());
            }
        }

        private void Compaire(string _originalUrl, string _DecryptedUrl)
        {
            // A static method is also available.
         String.Equals(_originalUrl, _DecryptedUrl, StringComparison.Ordinal);
            
   
        }

        private bool Decrypt (string _encryptedString, string _unEncryptedString){

            string _dencryptedString = " ";
            bool result = false; 
                byte[] unencryptedBytes = Encoding.ASCII.GetBytes(_encryptedString);
                byte[] cipherBytes = new byte[_encryptedString.Length];
                byte[] cipherText = Convert.FromBase64String(_encryptedString);
                using (AesManaged aesAlg = new AesManaged())
                {
                    aesAlg.Mode = CipherMode.ECB;
                    aesAlg.BlockSize = 128;
                    aesAlg.KeySize = 256;
                    aesAlg.Padding = PaddingMode.PKCS7;
                    aesAlg.Key = Encoding.ASCII.GetBytes(URL_ENCRYPTION_CODE);
                    //aesAlg.Key = URL_ENCRYPTION_CODE;

                   ////// Create a encrytor to perform the stream transform.
                    ICryptoTransform Dencryptor = aesAlg.CreateDecryptor(aesAlg.Key, aesAlg.IV);
                    using (MemoryStream msDencrypt = new MemoryStream(cipherText))
                    {
                        using (CryptoStream csDencrypt = new CryptoStream(msDencrypt, Dencryptor, CryptoStreamMode.Read))
                        {
                            using (StreamReader srEncrypt = new StreamReader(csDencrypt))
                            {
                                if (_encryptedString.Length != aesAlg.BlockSize)
                                { 
                                }
                                _dencryptedString = srEncrypt.ReadToEnd();
                               
                              return  String.Equals(_dencryptedString, _unEncryptedString, StringComparison.Ordinal);
                            }
                          
                        }
                    }
   
                }
            
        }
        private void btnExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void rdoErp100_CheckedChanged(object sender, EventArgs e)
        {
            ToggleErpFields(ErpType.Sage100);
        }

        private void rdoErp300_CheckedChanged(object sender, EventArgs e)
        {
            ToggleErpFields(ErpType.Sage300);
        }

        private void AddStates()
        {
            List<State> states = new List<State>()
            {
                new State{Abbreviation = "", Name = "None Selected"},
                new State{Abbreviation = "AK", Name = "Alaska"},
                new State{Abbreviation = "AL", Name = "Alabama"},
                new State{Abbreviation = "AR", Name = "Arkansas"},
                new State{Abbreviation = "AZ", Name = "Arizona"},
                new State{Abbreviation = "CA", Name = "California"},
                new State{Abbreviation = "CO", Name = "Colorado"},
                new State{Abbreviation = "CT", Name = "Connecticut"},
                new State{Abbreviation = "DC", Name = "District Of Columbia"},
                new State{Abbreviation = "DE", Name = "Delaware"},
                new State{Abbreviation = "FL", Name = "Florida"},
                new State{Abbreviation = "GA", Name = "Georgia"},
                new State{Abbreviation = "GU", Name = "Guam"},
                new State{Abbreviation = "HI", Name = "Hawaii"},
                new State{Abbreviation = "IA", Name = "Iowa"},
                new State{Abbreviation = "ID", Name = "Idaho"},
                new State{Abbreviation = "IL", Name = "Illinois"},
                new State{Abbreviation = "IN", Name = "Indiana"},
                new State{Abbreviation = "KS", Name = "Kansas"},
                new State{Abbreviation = "KY", Name = "Kentucky"},
                new State{Abbreviation = "LA", Name = "Louisiana"},
                new State{Abbreviation = "MA", Name = "Massachusetts"},
                new State{Abbreviation = "MD", Name = "Maryland"},
                new State{Abbreviation = "ME", Name = "Maine"},
                new State{Abbreviation = "MI", Name = "Michigan"},
                new State{Abbreviation = "MN", Name = "Minnesota"},
                new State{Abbreviation = "MO", Name = "Missouri"},
                new State{Abbreviation = "MS", Name = "Mississippi"},
                new State{Abbreviation = "MT", Name = "Montana"},
                new State{Abbreviation = "NC", Name = "North Carolina"},
                new State{Abbreviation = "ND", Name = "North Dakota"},
                new State{Abbreviation = "NE", Name = "Nebraska"},
                new State{Abbreviation = "NH", Name = "New Hampshire"},
                new State{Abbreviation = "NJ", Name = "New Jersey"},
                new State{Abbreviation = "NM", Name = "New Mexico"},
                new State{Abbreviation = "NV", Name = "Nevada"},
                new State{Abbreviation = "NY", Name = "New York"},
                new State{Abbreviation = "OH", Name = "Ohio"},
                new State{Abbreviation = "OK", Name = "Oklahoma"},
                new State{Abbreviation = "OR", Name = "Oregon"},
                new State{Abbreviation = "PA", Name = "Pennsylvania"},
                new State{Abbreviation = "PR", Name = "Puerto Rico"},
                new State{Abbreviation = "RI", Name = "Rhode Island"},
                new State{Abbreviation = "SC", Name = "South Carolina"},
                new State{Abbreviation = "SD", Name = "South Dakota"},
                new State{Abbreviation = "TN", Name = "Tennessee"},
                new State{Abbreviation = "TX", Name = "Texas"},
                new State{Abbreviation = "UT", Name = "Utah"},
                new State{Abbreviation = "VA", Name = "Virginia"},
                new State{Abbreviation = "VI", Name = "Virgin Islands"},
                new State{Abbreviation = "VT", Name = "Vermont"},
                new State{Abbreviation = "WA", Name = "Washington"},
                new State{Abbreviation = "WI", Name = "Wisconsin"},
                new State{Abbreviation = "WV", Name = "West Virginia"},
                new State{Abbreviation = "WY", Name = "Wyoming"}
            };

            cboCompanyState.DataSource = states;
            cboCompanyState.ValueMember = "Abbreviation";
            cboCompanyState.DisplayMember = "Name";
            cboCompanyState.SelectedIndex = 0;
        }

        private void ToggleErpFields(ErpType erpType)
        {
            txtCompanyName.Enabled = (erpType == ErpType.Sage300);
            txtCompanyAddress1.Enabled = (erpType == ErpType.Sage300);
            txtCompanyAddress2.Enabled = (erpType == ErpType.Sage300);
            txtCompanyCity.Enabled = (erpType == ErpType.Sage300);
            cboCompanyState.Enabled = (erpType == ErpType.Sage300);
            txtCompanyZip.Enabled = (erpType == ErpType.Sage300);

            if (erpType == ErpType.Sage100)
            {
                txtCompanyName.Text = string.Empty;
                txtCompanyAddress1.Text = string.Empty;
                txtCompanyAddress2.Text = string.Empty;
                txtCompanyCity.Text = string.Empty;
                cboCompanyState.SelectedIndex = 0;
                txtCompanyZip.Text = string.Empty;
            }
        }
    }

    public enum ErpType
    {
        Sage100 = 1, Sage300 = 3
    }

    public class State
    {
        public string Abbreviation { get; set; }
        public string Name { get; set; }
    }
}
