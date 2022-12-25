import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { BooksComponent } from './components/books/books.component';
import { LoginComponent } from './components/auth/login/login.component';
import { PageNotFoundComponent } from './components/page-not-found/page-not-found.component';
import { FormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';
import { RegisterComponent } from './components/auth/register/register.component';
import { JwtModule, JWT_OPTIONS } from '@auth0/angular-jwt';
import { NewBookComponent } from './components/books/components/new-book/new-book.component';
import { NewAuthorComponent } from './components/authors/components/new-author/new-author.component';
import { AuthorsComponent } from './components/authors/authors.component';
@NgModule({
  declarations: [
    AppComponent,
    BooksComponent,
    LoginComponent,
    PageNotFoundComponent,
    RegisterComponent,
    NewBookComponent,
    NewAuthorComponent,
    AuthorsComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,
    HttpClientModule,
    JwtModule.forRoot({
      config: {
        tokenGetter: (req) => {
            const token = req?.headers?.get("Authorization")?.replace("Bearer ", "");
            if(token == null)
              return "";

            return token;
        }
      }
    })
  ],
  providers: [],
  exports: [AppRoutingModule],
  bootstrap: [AppComponent]
})
export class AppModule { }
