import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { FormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';
import { JwtModule } from '@auth0/angular-jwt';
import { LoginPageComponent } from './ui/pages/login-page/login-page.component';
import { RegisterPageComponent } from './ui/pages/register-page/register-page.component';
import { DashboardPageComponent } from './ui/pages/dashboard-page/dashboard-page.component';
import { environment } from 'src/environments/environment';
import { CookieService } from 'ngx-cookie-service';
import { ProfilePageComponent } from './ui/pages/profile-page/profile-page.component';

export function getCookie(cookieService: CookieService, key: string): string {
  return cookieService.get(key);
}

@NgModule({
  declarations: [
    AppComponent,
    LoginPageComponent,
    RegisterPageComponent,
    DashboardPageComponent,
    ProfilePageComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,
    HttpClientModule,
    JwtModule.forRoot({// ovo omogucava da se jwt u header-u dodaje automatski kako se to ne bi radilo rucno
      config: {
        tokenGetter: () => localStorage.getItem('jwt'),
        allowedDomains: ['localhost:3000']  // ne radi ako je navedena sema
      }
    })
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
