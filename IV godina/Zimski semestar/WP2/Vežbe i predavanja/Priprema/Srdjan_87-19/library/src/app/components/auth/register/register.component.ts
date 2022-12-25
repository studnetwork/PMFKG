import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { AuthService } from '../../../core/services/auth/auth.service';
import { HttpErrorHandlerService } from 'src/app/core/services/error/http-error-handler.service';

/**
 * Kreirano sa: `ng g c components/auth/register`
 */
@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css']
})
export class RegisterComponent implements OnInit  {
  email: string = "";
  name: string = "";
  password: string = "";


  showErrorMsg = false;
  errorMessage = "";

  constructor(
    private authService: AuthService,
    private router: Router,
    private httpErrorHandler: HttpErrorHandlerService) {}
    
  ngOnInit(): void {
    if(this.authService.isLoggedIn())
      this.router.navigateByUrl("/");
  }

  register(): void {
    console.log(`register data: ${this.email}, ${this.name}, ${this.password}`)
    this.authService.register(this.email, this.name, this.password).subscribe({
      next: (token: string) => {
        
        console.log(`Restracija je uspesno obavljena. Dobijen je token: ${token}`);

        // this.authService.saveToken(token); moze da se iskoristi i da se na osnovu toka korisnik odmah uloguje
        this.showErrorMsg = false;
        this.router.navigateByUrl("/login");
      },
      error: (returnedError) => {
        this.showErrorMsg = true;
        this.errorMessage = this.httpErrorHandler.handle(returnedError);
      }}
    )
  }
}
