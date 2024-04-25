using Calculator;

namespace CalculatorUI
{
    public partial class CalculatorForm : Form
    {
        private readonly float[] _fontSizes = [55, 48, 41, 36, 34, 32, 29, 27, 25, 23, 22, 21, 20];

        private SimpleCalculator _calculator = new SimpleCalculator();

        private InputState _currentState = InputState.FirstOperand;

        public CalculatorForm()
        {
            InitializeComponent();
            inputTextBox.DataBindings.Add("Text", _calculator, "FirstOperand", false, DataSourceUpdateMode.OnPropertyChanged);
        }

        private enum InputState
        {
            FirstOperand,
            WaitingForSecondOperand,
            SecondOperand,
        }

        private void UpdateState(InputState state)
        {
            this._currentState = state;

            inputTextBox.DataBindings.Clear();

            if (state == InputState.WaitingForSecondOperand)
            {
                return;
            }

            var dataMember = state == InputState.FirstOperand ? "FirstOperand" : "SecondOperand";
            inputTextBox.DataBindings.Add("Text", _calculator, dataMember, false, DataSourceUpdateMode.OnPropertyChanged);
        }

        private void ButtonDigit_Click(object sender, EventArgs e)
        {
            if (this._currentState == InputState.WaitingForSecondOperand) 
            {
                this.UpdateState(InputState.SecondOperand);
            }

            if (this._currentState == InputState.SecondOperand && this._calculator.SecondOperand == double.NegativeInfinity
                || inputTextBox.Text == "Error")
            {
                inputTextBox.Text = string.Empty;
            }

            if (inputTextBox.Text.Length + 1 == 9)
            {
                return;
            }

            var button = (Button)sender;
            inputTextBox.Text += button.Text;

            if (inputTextBox.Text.Length > 6)
            {
                inputTextBox.Font = new Font(
                    "Arial Rounded MT Bold",
                    this._fontSizes[inputTextBox.Text.Length - 7],
                    FontStyle.Regular,
                    GraphicsUnit.Point, 0);
            }
        }

        private void ButtonOperator_Click(object sender, EventArgs e)
        {
            var button = (Button)sender;

            this.UpdateState(InputState.WaitingForSecondOperand);

            if (this._calculator.SecondOperand != double.NegativeInfinity)
            {
                this._calculator.FirstOperand = this._calculator.Calculate();
            }

            this._calculator.Operation = button.Text;

            inputTextBox.Text = this._calculator.FirstOperand.ToString();

            if (inputTextBox.Text.Length > 6)
            {
                inputTextBox.Font = new Font(
                    "Arial Rounded MT Bold",
                    this._fontSizes[inputTextBox.Text.Length - 7],
                    FontStyle.Regular,
                    GraphicsUnit.Point, 0);
            }
        }

        private void ButtonEqual_Click(object sender, EventArgs e)
        {
            this.UpdateState(InputState.FirstOperand);

            if (this._calculator.Operation == string.Empty || this._calculator.SecondOperand == double.NegativeInfinity)
            {
                this._calculator.SecondOperand = 0;
                this._calculator.Operation = "+";
            }

            try
            {
                this._calculator.FirstOperand = this._calculator.Calculate();
            }
            catch (DivideByZeroException) 
            {
                inputTextBox.Text = "Error";
                this._calculator.Reset();
                return;
            }

            inputTextBox.Text = this._calculator.FirstOperand.ToString();

            if (inputTextBox.Text.Length > 6)
            {
                inputTextBox.Font = new Font(
                    "Arial Rounded MT Bold",
                    this._fontSizes[inputTextBox.Text.Length - 7],
                    FontStyle.Regular,
                    GraphicsUnit.Point, 0);
            }
        }

        private void ButtonClear_Click(object sender, EventArgs e)
        {
            if (this._currentState != InputState.FirstOperand)
            {
                this.UpdateState(InputState.FirstOperand);
            }

            inputTextBox.Text = string.Empty;

            this._calculator.Reset();
        }
    }
}
